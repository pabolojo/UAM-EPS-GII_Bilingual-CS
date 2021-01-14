from django.db import models
import django
from django.db.models.functions import Upper


class Teacher(models.Model):
    '''
    Class: Teacher
    Description: Class that declares how the Teacher object
    is defined inside the database
    '''
    max_length = 128
    first_name = models.CharField(max_length=max_length)
    last_name = models.CharField(max_length=max_length)

    class Meta:
        ordering = (Upper('last_name'), 'first_name')

    def __str__(self):
        return str(self.last_name) + ", " + str(self.first_name)


class LabGroup(models.Model):
    '''
    Class: LabGroup
    Description: Class that declares how the LabGroup object
    is defined inside the database
    '''
    max_length = 128
    teacher = models.ForeignKey(Teacher, on_delete=models.SET_NULL, null=True)
    groupName = models.CharField(max_length=max_length)
    language = models.CharField(max_length=max_length)
    schedule = models.CharField(max_length=max_length)
    maxNumberStudents = models.IntegerField(default=30)
    counter = models.IntegerField(default=0)

    class Meta:
        ordering = ('groupName', )

    def __str__(self):
        return str(self.groupName) + " (teacher: " + str(self.teacher) + ")" +\
            " - schedule: " + str(self.schedule)


class TheoryGroup(models.Model):
    '''
    Class: Theory Group
    Description: Class that declares how the TheoryGroup object
    is defined inside the database
    '''
    max_length = 128
    groupName = models.CharField(max_length=max_length)
    language = models.CharField(max_length=max_length)

    class Meta:
        ordering = ('groupName', )

    def __str__(self):
        return self.groupName


class Student(django.contrib.auth.models.User):
    '''
    Class: Student
    Description: Class that declares how the Student object
    is defined inside the database, it inherits from User
    '''
    max_length = 128
    labGroup = models.ForeignKey(
        LabGroup, on_delete=models.SET_NULL, null=True)
    theoryGroup = models.ForeignKey(
        TheoryGroup, on_delete=models.SET_NULL, null=True)
    gradeTheoryLastYear = models.DecimalField(decimal_places=2, max_digits=4,
                                              default=0)
    gradeLabLastYear = models.DecimalField(decimal_places=2, max_digits=4,
                                           default=0)
    convalidationGranted = models.BooleanField(default=False)

    class Meta:
        ordering = (Upper('last_name'), 'first_name')

    def __str__(self):
        return str(self.last_name) + ", " + str(self.first_name)


class Pair(models.Model):
    '''
    Class: Pair
    Description: Class that declares how the Pair object
    is defined inside the database
    '''
    student1 = models.ForeignKey(
        Student, on_delete=models.CASCADE, related_name='+')
    student2 = models.ForeignKey(
        Student, on_delete=models.CASCADE, related_name='+')
    validated = models.BooleanField(default=False)
    studentBreakRequest = models.ForeignKey(
        Student, on_delete=models.SET_NULL, null=True, related_name='+')

    def __str__(self):
        return str(self.student1) + " and " + str(self.student2)


class GroupConstraints(models.Model):
    '''
    Class: GroupConstraints
    Description: Class that declares how the GroupConstraints object
    is defined inside the database
    '''
    theoryGroup = models.ForeignKey(
        TheoryGroup, on_delete=models.SET_NULL, null=True)
    labGroup = models.ForeignKey(
        LabGroup, on_delete=models.SET_NULL, null=True)

    class Meta:
        ordering = ('labGroup', 'theoryGroup')

    def __str__(self):
        return str(self.theoryGroup) + " " + str(self.labGroup)


class OtherConstraints(models.Model):
    '''
    Class: OtherConstraints
    Description: Class that declares how the OtherConstraints object
    is defined inside the database
    '''
    selectGroupStartDate = models.DateField()
    minGradeTheoryConv = models.DecimalField(decimal_places=2, max_digits=4,
                                             default=5)
    minGradeLabConv = models.DecimalField(decimal_places=2, max_digits=4,
                                          default=5)

    def __str__(self):
        return str(self.minGradeTheoryConv) + " " + str(self.minGradeLabConv)


