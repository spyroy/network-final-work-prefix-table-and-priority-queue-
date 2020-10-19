to compile write in terminal: make

to run prefix_table write in terminal: ./prefix_table <input_file>
where input_file is a txt file with commands such ADD,FIND,REMOVE
each in a different row, all with capitals (won't run otherwise) for example:

ADD 255.255.255.0/24 A
FIND 255.255.255.255
REMOVE 255.255.255.0/24 A

to run prefix_table_opt write in terminal: ./prefix_table_opt <input_file>
where input_file is a txt file with commands such ADD,FIND,REMOVE
each in a different row, all with capitals (won't run otherwise) for example:

ADD 255.255.255.0/24 A
FIND 255.255.255.255
REMOVE 255.255.255.0/24 A

in this version prefixes differ in one bit will be united.
