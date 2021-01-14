import datetime
from django.utils import timezone
from django.urls import reverse
from core.models import (Student, OtherConstraints,
                         Pair, TheoryGroup, GroupConstraints,
                         LabGroup)
from core.tests_services import ServiceBaseTest


class AdditionalTests(ServiceBaseTest):
    ''' Class for the additional tests to get a
    100% coverage testing'''

    def setUp(self):
        # SetUp the class
        super().setUp()

    def tearDown(self):
        # Clean the database
        self.populate.cleanDataBase()

    def test_1_home_no_logged(self):
        # Test that when no user is logged in,
        # the home page contains the message
        # "This web site allows EDAT students to"...
        response = self.client1.get(reverse('core:home'),
                                    follow=True)
        self.assertTrue(self.decode(response.content).
                        find("This web site allows EDAT students to") != -1)

    def test_2_bad_login(self):
        # Test that checks that if we provide bad credentials to the
        # login page we will be redirected to a page showing us the
        # error
        data = {'username': 'alumnodb',
                'password': 'bad_pass'}
        response = self.client1.post(reverse('core:login'),
                                     data=data,
                                     follow=True)

        self.assertTrue(self.decode(response.content).
                        find("Username or password incorrect") != -1)

    def test_3_valid_pair_group_full(self):
        # Check that when a user with a valid pair applies to
        # a group, both members of the pair are added to it
        "disable labgroup when full"
        # login
        self.loginTestUser(self.client1, self.user1)
        # assign theory group to users
        theoryGroup = TheoryGroup.objects.all().first()
        self.user1.theoryGroup = theoryGroup
        self.user1.save()
        self.user2.theoryGroup = theoryGroup
        self.user2.save()
        # We create the valid pair user1 - user2
        Pair.objects.get_or_create(
            student1=self.user1, student2=self.user2, validated=True)
        # set othercostraint.selectGroupStart to now
        o = OtherConstraints.objects.all().first()
        now = datetime.datetime.now()
        now = timezone.make_aware(now, timezone.get_current_timezone())
        o.selectGroupStartDate = now
        o.save()
        # assign maximum number of students and count to labGroup
        labGroup = GroupConstraints.objects.filter(
            theoryGroup=theoryGroup).first().labGroup
        labGroup.counter = 1
        labGroup.maxNumberStudents = 2
        labGroup.save()
        # try to reserve
        labGroupId = labGroup.id
        data = {'labId': labGroupId}
        self.client1.post(reverse('core:applygroup'),
                          data=data,
                          follow=True)
        # refresh user
        user = Student.objects.get(pk=self.user1.id)
        user2 = Student.objects.get(pk=self.user2.id)
        self.assertIsNone(user.labGroup)
        self.assertIsNone(user2.labGroup)
        self.assertEqual(labGroup.counter, 1)
        # increase maxNumberStudents
        labGroup.counter = 1
        labGroup.maxNumberStudents = 3
        labGroup.save()
        # try to reserve
        labGroupId = labGroup.id
        data = {'labId': labGroupId}
        self.client1.post(reverse('core:applygroup'),
                          data=data,
                          follow=True)
        # refresh users and labGroup
        user = Student.objects.get(pk=self.user1.id)
        user2 = Student.objects.get(pk=self.user2.id)
        labGroup = LabGroup.objects.get(pk=labGroup.id)
        self.assertEqual(user.labGroup.id, labGroup.id)
        self.assertEqual(user2.labGroup.id, labGroup.id)
        self.assertEqual(labGroup.counter, 3)
