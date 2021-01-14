# http://www.dpriver.com/pp/sqlformat.htm
# Version 1.2
# Modificacion
# 1) Las consultas 1 y 2 se han intercambiado para que sigan el mismo orden
#    que en el enunciado de la práctica
# 2) se ha añadido la opción allqueries la cual ejecuta todas las consultas
# Por lo general no se requiere modificar el fichero

GRUPO=1291
PAREJA=31

export PGDATABASE:=dvdrental
export PGDATABASE2:=newdatabase
export PGUSER :=alumnodb
export PGPASSWORD :=alumnodb
export PGCLIENTENCODING:=LATIN9
export PGHOST:=localhost

DBNAME =$(PGDATABASE)
DBNAME2 =$(PGDATABASE2)
PSQL = psql
CREATEDB = createdb
DROPDB = dropdb --if-exists
PG_DUMP = pg_dump
PG_RESTORE = pg_restore

all: dropdb createdb restore

newdatabase:
	@echo Eliminando BBDD
	@$(DROPDB) $(DBNAME2)
	rm -f *.log
	@echo Creating the redesign database
	@$(CREATEDB) $(DBNAME2)
	@echo restore data base 2
	psql -U $(PGUSER) -d $(DBNAME2) -1 -f $(PGDATABASE2).sql


createdb:
	@echo Creando BBDD
	@$(CREATEDB)
dropdb:
	@echo Eliminando BBDD
	@$(DROPDB) $(DBNAME)
	rm -f *.log
dropnewdb:
	@echo Eliminando BBDD
	@$(DROPDB) $(DBNAME2)
	rm -f *.log
dump:
	@echo creando dumpfile
	@$(PG_DUMP) > $(DBNAME).sql
restore:
	@echo restore data base
	@cat $(DBNAME).sql | $(PSQL)
shell:
	@echo create psql shell
	@$(PSQL)

allqueries: query1 query2 query3 query4 query5 query6
	@cat query?.log > all_queries.log

query1:
	@echo query-1: "Movies rented each year" | tee query1.log
	@cat query1.sql | $(PSQL) | tee -a query1.log
query2:
	@echo query-2: "Customer who has rented more movies" | tee query2.log
	@cat query2.sql | $(PSQL) | tee -a query2.log
query3:
	@echo query3: "Cities where movies, in which “Bob Fawcett” appears, have been rented" | tee query3.log
	@cat query3.sql | $(PSQL) | tee -a query3.log
query4:
	@echo query4: "Language in which most of the films have been filmed" | tee query4.log
	@cat query4.sql | $(PSQL) | tee -a query4.log
query5:
	@echo query5: "Language in which a greater number of rentals has been done" | tee query5.log
	@cat query5.sql | $(PSQL) | tee -a query5.log
query6:
	@echo query6: "Favorite category of the customer who has rented more movies" | tee query6.log
	@cat query6.sql | $(PSQL) | tee -a query6.log
