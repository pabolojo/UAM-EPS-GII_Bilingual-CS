# Populate database
# This file has to be placed within the
# core/management/commands directory in your project.
# If that directory doesn't exist, create it.
# The name of the script is the name of the custom command,
# that is, populate.py.
#
# execute python manage.py  populate


from django.core.management.base import BaseCommand
from core.models import (OtherConstraints, Pair, Student,
                         GroupConstraints, TheoryGroup,
                         LabGroup, Teacher)
import datetime
from collections import OrderedDict

import csv


def add_teacher(id, first_name, last_name):
    '''
    Method: add_teacher
    Description: Adds a teacher to the database
    Input parameters: id, fisrt name and last name of
    the teacher to be inserted
    Return: Void
    '''
    t = Teacher.objects.get_or_create(id=id, first_name=first_name,
                                      last_name=last_name)[0]
    t.save()
    return


def add_labgroup(id,  teacher, groupName, language,
                 schedule, maxNumberStudents):
    '''
    Method: add_labgroup
    Description: Adds a labgroup to the database
    Input parameters: id,  teacher, groupName, language, schedule,
                    maxNumberStudents of the labgroup to be inserted
    Return: Void
    '''
    t = Teacher.objects.filter(id=teacher).first()
    lg = LabGroup.objects.get_or_create(
        id=id,  teacher=t, groupName=groupName,
        language=language, schedule=schedule,
        maxNumberStudents=maxNumberStudents)[0]
    lg.save()
    return


def add_theorygroup(id, groupName, language):
    '''
Method: add_theorygroup
Description: Adds a theory group to the database
Input parameters: id, group name and language of the
theory group to be inserted
Return: Void
'''
    tg = TheoryGroup.objects.get_or_create(
        id=id, groupName=groupName, language=language)[0]
    tg.save()
    return


def add_groupconstraints(theoryGroup, labGroup):
    '''
Method: add_groupconstraints
Description: Adds a Group Constrain to the database
Input parameters: theoryGroup, labGroup of the Group Constrain to be inserted
Return: Void
'''
    tg = TheoryGroup.objects.filter(id=theoryGroup).first()
    lg = LabGroup.objects.filter(id=labGroup).first()
    gc = GroupConstraints.objects.get_or_create(
        theoryGroup=tg, labGroup=lg)[0]
    gc.save()
    return


def add_student(id, nie, dni, apellidos, nombre, theoryGroup):
    '''
Method: add_student
Description: Adds a student to the database
Input parameters: id, nie, dni last name, first name and
theory group of the student to be inserted
Return: Void
'''
    tg = TheoryGroup.objects.filter(id=theoryGroup).first()
    s = Student.objects.get_or_create(
        id=id, theoryGroup=tg, username=nie, first_name=nombre,
        last_name=apellidos, convalidationGranted=False)[0]
    s.set_password(dni)
    s.save()
    return s


def update_student(nie, theoryGrade, labGrade):
    '''
Method: update_student
Description: Update a student of the database
Input parameters: tnie, theoryGrade, labGrade to be updated
Return: Void
'''
    s = Student.objects.filter(username=nie).first()
    s.gradeTheoryLastYear = theoryGrade
    s.gradeLabLastYear = labGrade
    """oc = OtherConstraints.objects.first()
    if (float(theoryGrade) > float(oc.minGradeTheoryConv)
            and float(labGrade) > float(oc.minGradeLabConv)):
        s.convalidationGranted = True"""
    s.save()
    return


def add_pairD(ids1, ids2, validated):
    '''
Method: add_teacher
Description: Adds a pair to the database
Input parameters: id of the fisrt student, id of the second
student and if the pair is valdated or not
Return: Void
'''
    s1 = Student.objects.filter(id=ids1).first()
    s2 = Student.objects.filter(id=ids2).first()
    if Pair.objects.filter(student1=s1, student2=s2).first() is not None:
        return
    p = Pair.objects.get_or_create(
        student1=s1, student2=s2, validated=validated)[0]
    p.save()
    return

# The name of this class is not optional must be Command
# otherwise manage.py will not process it properly
#
# Teachers, groups and constraints
# will be hardcoded in this file.
# Students will be read from a csv file
# last year grade will be obtained from another csv file


class Command(BaseCommand):
    # helps and arguments shown when command python manage.py help populate
    # is executed.
    help = """populate database
           """

    def add_arguments(self, parser):
        parser.add_argument('model', type=str, help="""
        model to  update:
        all -> all models
        teacher
        labgroup
        theorygroup
        groupconstraints
        otherconstrains
        student (require csv file)
        studentgrade (require different csv file,
        update only existing students)
        pair
        """)
        parser.add_argument('studentinfo', type=str, help="""CSV file with student information
        header= NIE, DNI, Apellidos, Nombre, Teoría
        if NIE or DNI == 0 skip this entry and print a warning""")
        parser.add_argument('studentinfolastyear', type=str, help="""CSV file with student information
        header= NIE,DNI,Apellidos,Nombre,Teoría, grade lab, grade the
        if NIE or DNI == 0 skip this entry and print a warning""")

    # handle is another compulsory name, do not change it"
    def handle(self, *args, **kwargs):
        model = kwargs['model']
        csvStudentFile = kwargs['studentinfo']
        csvStudentFileGrades = kwargs['studentinfolastyear']
        # clean database
        if model == 'all':
            self.cleanDataBase()
        if model == 'teacher' or model == 'all':
            self.teacher()
        if model == 'labgroup' or model == 'all':
            self.labgroup()
        if model == 'theorygroup' or model == 'all':
            self.theorygroup()
        if model == 'groupconstraints' or model == 'all':
            self.groupconstraints()
        if model == 'otherconstrains' or model == 'all':
            self.otherconstrains()
        if model == 'student' or model == 'all':
            self.student(csvStudentFile)
        if model == 'studentgrade' or model == 'all':
            self.studentgrade(csvStudentFileGrades)
        if model == 'pair' or model == 'all':
            self.pair()

    def cleanDataBase(self):
        Teacher.objects.all().delete()
        OtherConstraints.objects.all().delete()
        Pair.objects.all().delete()
        Student.objects.all().delete()
        GroupConstraints.objects.all().delete()
        TheoryGroup.objects.all().delete()
        LabGroup.objects.all().delete()
        return

    def teacher(self):
        teacherD = []
        teacherD.append({'id': 1,  # 1261, L 18:00, 1271 X 18-20
                         'first_name': 'No',
                         'last_name': 'Asignado1', })
        teacherD.append({'id': 2,  # 1262 X 18-20, 1263/1273 V 17-19
                         'first_name': 'No',
                         'last_name': 'Asignado4', })
        teacherD.append({'id': 3,  # 1272 V 17-19, 1291 L 18-20
                         'first_name': 'Julia',
                         'last_name': 'Diaz Garcia', })
        teacherD.append({'id': 4,  # 1292/1251V 17:00
                         'first_name': 'Alvaro',
                         'last_name': 'del Val Latorre', })
        teacherD.append({'id': 5,  # 1201 X 18:00
                         'first_name': 'Roberto',
                         'last_name': 'Marabini Ruiz', })

        for teacher in teacherD:
            add_teacher(teacher['id'], teacher['first_name'],
                        teacher['last_name'])
        return

    def labgroup(self):
        labgroupD = []
        maxNumberStudents = 23
        # create dictionary with teacher data
        labgroupD.append({'id': 1261,  # 1261, L 18:00, 1271 X 18-20
                          'groupName': '1261',
                          'teacher': 1,
                          'schedule': 'Lunes/Monday 18-20',
                          'language': 'español/Spanish',
                          'maxNumberStudents': maxNumberStudents})
        labgroupD.append({'id': 1262,  # 1261, L 18:00, 1271 X 18-20
                          'teacher': 2,
                          'groupName': '1262',
                          'schedule': 'Miércoles/Wednesday 18-20',
                          'language': 'español/Spanish',
                          'maxNumberStudents': maxNumberStudents})
        labgroupD.append({'id': 1263,  # 1261, L 18:00, 1271 X 18-20
                          'teacher': 2,
                          'groupName': '1263',
                          'schedule': 'Viernes/Friday 17-19',
                          'language': 'español/Spanish',
                          'maxNumberStudents': maxNumberStudents})
        labgroupD.append({'id': 1271,  # 1261, L 18:00, 1271 X 18-20
                          'teacher': 1,
                          'groupName': '1271',
                          'schedule': 'Miércoles/Wednesday 18-20',
                          'language': 'español/Spanish',
                          'maxNumberStudents': maxNumberStudents})
        labgroupD.append({'id': 1272,  # 1261, L 18:00, 1271 X 18-20
                          'teacher': 3,
                          'groupName': '1272',
                          'schedule': 'Viernes/Friday 17-19',
                          'language': 'español/Spanish',
                          'maxNumberStudents': maxNumberStudents})
        labgroupD.append({'id': 1291,  # 1261, L 18:00, 1271 X 18-20
                          'teacher': 3,
                          'groupName': '1291',
                          'schedule': 'Lunes/Monday 18-20',
                          'language': 'inglés/English',
                          'maxNumberStudents': maxNumberStudents})
        labgroupD.append({'id': 1292,
                          'teacher': 4,
                          'groupName': '1292',
                          'schedule': 'Viernes/Friday 17-19',
                          'language': 'inglés/English',
                          'maxNumberStudents': maxNumberStudents})
        labgroupD.append({'id': 1201,
                          'teacher': 5,
                          'groupName': '1201',
                          'schedule': 'Miércoles/Wednesday 18-20',
                          'language': 'español/Spanish',
                          'maxNumberStudents': maxNumberStudents})

        for labgroup in labgroupD:
            add_labgroup(labgroup['id'],
                         labgroup['teacher'],
                         labgroup['groupName'],
                         labgroup['language'], labgroup['schedule'],
                         labgroup['maxNumberStudents'])
        return

    def theorygroup(self):
        theorygroupD = []
        theorygroupD.append({'id': 126,
                             'groupName': '126',
                             'language': 'español/Spanish', })
        theorygroupD.append({'id': 127,  # 127/120
                             'groupName': '127',
                             'language': 'español/Spanish', })
        theorygroupD.append({'id': 129,  # 129/125
                             'groupName': '129',
                             'language': 'inglés/English', })
        theorygroupD.append({'id': 120,  # 127/120
                             'groupName': '120',
                             'language': 'español/Spanish', })
        theorygroupD.append({'id': 125,  # 129/125
                             'groupName': '125',
                             'language': 'inglés/English', })

        for theorygroup in theorygroupD:
            add_theorygroup(
                theorygroup['id'], theorygroup['groupName'],
                theorygroup['language'])
        return

    def groupconstraints(self):
        """ Follows which laboratory groups (4th column
            may be choosen by which theory groups (2nd column)
            theoryGroup: 126, labGroup: 1261
            theoryGroup: 126, labGroup: 1262
            theoryGroup: 126, labGroup: 1263
            theoryGroup: 127, labGroup: 1271
            theoryGroup: 127, labGroup: 1272
            theoryGroup: 120, labGroup: 1201
            theoryGroup: 129, labGroup: 1291
            theoryGroup: 125, labGroup: 1292"""

        groupconstraintsD = []
        groupconstraintsD.append(
            {'theoryGroup': 126, 'labGroup': 1261})  # mañana
        groupconstraintsD.append(
            {'theoryGroup': 126, 'labGroup': 1262})  # mañana
        groupconstraintsD.append(
            {'theoryGroup': 126, 'labGroup': 1263})  # mañana
        # tarde, split ii and doble
        groupconstraintsD.append(
            {'theoryGroup': 127, 'labGroup': 1271})  # tarde - no doble
        groupconstraintsD.append(
            {'theoryGroup': 127, 'labGroup': 1272})  # tarde - no doble
        # doble - tarde - español - WEds
        groupconstraintsD.append({'theoryGroup': 120, 'labGroup': 1201})
        # english
        # inglés - ii - tarde Friday
        groupconstraintsD.append({'theoryGroup': 129, 'labGroup': 1291})
        groupconstraintsD.append(
            {'theoryGroup': 125, 'labGroup': 1292})  # inglés - doble
        # groupconstraintsD[1202] = {'theoryGroup' : 120, 'labGroup': 1202}
        # # doble - tarde - 2nd group
        for groupconstraints in groupconstraintsD:
            add_groupconstraints(
                groupconstraints['theoryGroup'], groupconstraints['labGroup'])
        return

    def pair(self):
        """ create two requests
            1000 -> 1100
            1001 -> 1001
            create three verified groups
            1010 - 1110
            1011 - 1111
            1012 - 1112
        """
        pairD = OrderedDict()
        # Mañana
        pairD[1000] = {'student2': 1100, 'validated': False}
        pairD[1001] = {'student2': 1101, 'validated': False}
        pairD[1010] = {'student2': 1110, 'validated': True}
        pairD[1011] = {'student2': 1111, 'validated': True}
        pairD[1012] = {'student2': 1112, 'validated': True}

        for pair, pair_data in pairD.items():
            add_pairD(pair, pair_data['student2'], pair_data['validated'])
        return

    def otherconstrains(self):
        """create a single object here with staarting dates
        and maximum and minimum convalidation grades"""
        """ Use the following values:
        selectGroupStartDate = now + 1 day,
        minGradeTheoryConv = 3,
        minGradeLabConv = 7
        """
        date = datetime.date.today() + datetime.timedelta(days=1)
        oc = OtherConstraints.objects.get_or_create(
            selectGroupStartDate=date, minGradeTheoryConv=3,
            minGradeLabConv=7)[0]
        oc.save()
        return

    def student(self, csvStudentFile):
        '''
    Method: student
    Description: It will create in the database all the students
    that are present in the CSV file passed as argument
    Input parameters: self, csvStudentFile
    Return: Void
    '''
        # read csv file
        # structure NIE	DNI	Apellidos	Nombre	group-Teoría
        i = 1000
        with open(csvStudentFile, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                add_student(i, row['NIE'], row['DNI'], row['Apellidos'],
                            row['Nombre'], row['grupo-teoria'])
                i = i + 1
        return

    def studentgrade(self, csvStudentFileGrades):
        '''
        Method: studentgrade
        Description: Updates last year grades of the
        students who had failed the subject
        Input parameters: the file where the data is stored (.csv)
        Return: Void
        '''
        # read csv file
        # structure NIE	DNI	Apellidos	Nombre	group-Teoría
        # grade-practicas	gradeteoria
        # remove pass and ADD CODE HERE
        with open(csvStudentFileGrades, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                update_student(row['NIE'], row['nota-teoria'],
                               row['nota-practicas'])
        return


