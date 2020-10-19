to compile write in terminal: make

to run edf write in terminal: ./edf <queue_size> <input_file>
whaen queue_size is the size of the processes queue and input_file is a file with processes, each process is a trio <amount,slack,value>
and each line in the input_file represent the time unit that the process came

to run bd to run edf write in terminal: ./bd <queue_size> <input_file>
whaen queue_size is the size of the processes queue and input_file is a file with processes, each process is a trio <amount,slack,value>
and each line in the input_file represent the time unit that the process came

edf sort the queue by slack and bd by value.
