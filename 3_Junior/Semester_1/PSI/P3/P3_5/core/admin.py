from django.contrib import admin
from core.models import (OtherConstraints, Pair, Student,
                         GroupConstraints, TheoryGroup,
                         LabGroup, Teacher)

# We register the models of the application in the admin panel
# So we can delete or insert objects
admin.site.register(Teacher)
admin.site.register(OtherConstraints)
admin.site.register(Pair)
admin.site.register(Student)
admin.site.register(GroupConstraints)
admin.site.register(TheoryGroup)
admin.site.register(LabGroup)
