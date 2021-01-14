from django import forms
from core.models import (Student,
                         Pair, GroupConstraints,
                         LabGroup)
from django.db.models import Q


class PairForm(forms.Form):
    '''
    Class: PairForm
    Description: Form to receive the student that the actual user
    want to be paired with
    '''
    # Field to be filled
    student2 = forms.ModelChoiceField(
        queryset=None, label="Select second member of the pair")

    def __init__(self, *args, **kwargs):
        # We store the actual user passed as argument
        user = kwargs.pop('user', None)
        super(PairForm, self).__init__(*args, **kwargs)
        # We ensure that a user parameter has been passed
        if user:
            # We get a list of students excluding the admin and the user who
            # makes the request
            self.fields['student2'].queryset = Student.objects.all().exclude(
                Q(id=user.id) | Q(id=2))
            students = list(self.fields['student2'].queryset)
            for student in students:
                # We filter the students that are in a validated pair
                if not (len(Pair.objects.filter((Q(student1=student) |
                                                 Q(student2=student))
                                                & Q(validated=True)))
                        == 0):
                    self.fields['student2'].queryset =\
                        self.fields['student2'].queryset.exclude(
                        id=student.id)


class GroupForm(forms.Form):
    '''
    Class: GroupForm
    Description: Class in charge of creating the form for group selection
    '''
    labId = forms.ModelChoiceField(
        queryset=None, label="Select labGroup")

    def __init__(self, *args, **kwargs):
        # we retrieve theuser argument
        user = kwargs.pop('user', None)
        super(forms.Form, self).__init__(*args, **kwargs)
        if user:
            # we get the valid pairs where user is one of its members
            pair = Pair.objects.filter((Q(student1=user) |
                                        Q(student2=user)) & Q(validated=True))

            # we exclude all the lab groups that are not related with the
            # theory group which the user belongs to
            self.fields['labId'].queryset = LabGroup.objects.all()
            groups = list(GroupConstraints.objects.all().filter(
                theoryGroup=user.theoryGroup))
            aux = []
            for g in groups:
                aux.append(g.labGroup.groupName)

            self.fields['labId'].queryset =\
                self.fields['labId'].queryset.filter(groupName__in=aux)

            # we filter out the groups that do not have enought space to hold
            # our user or our user and its valid partner
            groups = list(self.fields['labId'].queryset)
            if len(pair) == 0:
                for g in groups:
                    if g.counter >= g.maxNumberStudents:
                        self.fields['labId'].queryset =\
                            self.fields['labId'].queryset.exclude(
                            groupName=g.groupName)
            else:
                for g in groups:
                    if g.counter + 1 >= g.maxNumberStudents:
                        self.fields['labId'].queryset =\
                            self.fields['labId'].queryset.exclude(
                            groupName=g.groupName)


