import datetime
from django.utils import timezone
from django.urls import reverse
from core.models import (OtherConstraints,
                         Pair, TheoryGroup, GroupConstraints)
from core.tests_services import ServiceBaseTest


class AdditionalTestsP4(ServiceBaseTest):
    ''' Class for the additional tests to get a
    100% coverage testing'''

    def setUp(self):
        # SetUp the class
        super().setUp()

    def tearDown(self):
        # Clean the database
        self.populate.cleanDataBase()

    def test_1_member_has_labgroup(self):
        # Check that when a user in a LabGroup tries
        # to break a pair, the system does not allow him
        # to find the pair in the group

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
        labGroup.counter = 0
        labGroup.maxNumberStudents = 3
        labGroup.save()
        # try to reserve
        labGroupId = labGroup.id
        data = {'labId': labGroupId}
        self.client1.post(reverse('core:applygroup'),
                          data=data,
                          follow=True)

        # Check that when a user in a LabGroup tries
        # to break a pair, the system does not allow him
        # to find the pair in the break pair selector
        response = self.client1.get(reverse('core:breakpair'),
                                    follow=True)
        self.assertTrue(self.decode(response.content).
                        find(str(self.user1) + " and "
                             + str(self.user2)) == -1)
