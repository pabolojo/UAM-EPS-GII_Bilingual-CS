import os
import django
import datetime

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'labassign.settings')
django.setup()

import core.management.commands.populate as p
from core.models import (OtherConstraints, Pair, Student)

from labassign.settings import BASE_DIR
pathToProject = BASE_DIR


if __name__ == "__main__":
    s1 = Student.objects.filter(id=1000).first()
    s2 = Student.objects.filter(id=1001).first()
    if s1 is None:
        s1 = p.add_student(1000, 12345678, 123456,
    if s2 is None:
        s2 = p.add_student(1001, 12345679, 123457,

    p.add_pairD(1000, 1001, False)
    for pair in Pair.objects.filter(student1=s1):
        print(pair)
        pair.validated = True
        pair.save()

    date = datetime.date.today() + datetime.timedelta(days=1)
    oc = OtherConstraints.objects.get_or_create(selectGroupStartDate=date)[0]
    oc.save()

    c = OtherConstraints.objects.first()
    if c.selectGroupStartDate > datetime.date.today():
        print("The start date is in the future")
    else:
        print("The start date is in the past")


