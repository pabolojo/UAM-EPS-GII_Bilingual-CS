# Generated by Django 2.2.5 on 2020-11-08 11:45

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('core', '0007_auto_20201108_1124'),
    ]

    operations = [
        migrations.AlterField(
            model_name='student',
            name='gradeLabLastYear',
            field=models.DecimalField(decimal_places=2, default=0, max_digits=4),
        ),
        migrations.AlterField(
            model_name='student',
            name='gradeTheoryLastYear',
            field=models.DecimalField(decimal_places=2, default=0, max_digits=4),
        ),
    ]
