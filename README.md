# SP-Project_2

Use:
	Part_2 centers around using multithreading rather than multiporocessing. 

Discription:
	Find directory and file and create a new thread for each respectively. 

Updates:
	11/23 - Ok so the problem is not as bad as we thought. The entry where it segfaults on is the LAST one of the second file. So our inner data structure stores 2 csv files worth of data but screws up on the very last line. I had it print out the index it is working on and is segfaults on 10058 which is twice the amount of line numbers in one csv file.
