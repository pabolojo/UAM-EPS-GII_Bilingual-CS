# Generated by Django 2.2.5 on 2020-11-01 18:47

from django.conf import settings
import django.contrib.auth.models
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        ('auth', '0011_update_proxy_permissions'),
    ]

    operations = [
        migrations.CreateModel(
            name='LabGroup',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('groupName', models.CharField(max_length=128)),
                ('language', models.CharField(max_length=128)),
                ('schedule', models.CharField(max_length=128)),
                ('maxNumberStudents', models.IntegerField(default=30)),
                ('counter', models.IntegerField(default=0)),
            ],
            options={
                'ordering': ('groupName',),
            },
        ),
        migrations.CreateModel(
            name='OtherConstraints',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('selectGroupStartDate', models.DateField()),
                ('minGradeTheoryConv', models.DecimalField(decimal_places=2, max_digits=4)),
                ('minGradeLabConv', models.DecimalField(decimal_places=2, max_digits=4)),
            ],
        ),
        migrations.CreateModel(
            name='Teacher',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('first_name', models.CharField(max_length=128)),
                ('last_name', models.CharField(max_length=128)),
            ],
            options={
                'ordering': ('last_name', 'first_name'),
            },
        ),
        migrations.CreateModel(
            name='TheoryGroup',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('groupName', models.CharField(max_length=128)),
                ('language', models.CharField(max_length=128)),
            ],
            options={
                'ordering': ('groupName',),
            },
        ),
        migrations.CreateModel(
            name='Student',
            fields=[
                ('user_ptr', models.OneToOneField(auto_created=True, on_delete=django.db.models.deletion.CASCADE, parent_link=True, primary_key=True, serialize=False, to=settings.AUTH_USER_MODEL)),
                ('gradeTheoryLastYear', models.DecimalField(decimal_places=2, max_digits=4, null=True)),
                ('gradeLabLastYear', models.DecimalField(decimal_places=2, max_digits=4, null=True)),
                ('convalidationGranted', models.BooleanField()),
                ('labGroup', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='core.LabGroup')),
                ('theoryGroup', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='core.TheoryGroup')),
            ],
            options={
                'ordering': ('last_name', 'first_name'),
            },
            bases=('auth.user',),
            managers=[
                ('objects', django.contrib.auth.models.UserManager()),
            ],
        ),
        migrations.CreateModel(
            name='Pair',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('validated', models.BooleanField()),
                ('student1', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='+', to='core.Student')),
                ('student2', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='+', to='core.Student')),
                ('studentBreakRequest', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, related_name='+', to='core.Student')),
            ],
        ),
        migrations.AddField(
            model_name='labgroup',
            name='teacher',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='core.Teacher'),
        ),
        migrations.CreateModel(
            name='GroupConstraints',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('labGroup', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='core.LabGroup')),
                ('theoryGroup', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='core.TheoryGroup')),
            ],
            options={
                'ordering': ('theoryGroup', 'labGroup'),
            },
        ),
    ]