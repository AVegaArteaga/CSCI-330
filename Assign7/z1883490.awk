 # CSCI 330, Assignment 7, Fall Semester
 # Abel Vega Arteaga
 # z1883490
 # Section 1
 # December 2, 2019
 # Purpose: You must write an awk script that will generate a report when supplied input data in a specified format
 # 	Your awk script must compute summary data on the performance of sales associates for the company No-op Computing........"

BEGIN{
	FS = ":" # this is what we will be used to seperating the fieleds
	yearTarget=2018 # The assignment SPECIFCALLY ask for 2018, this will filter out any data that is not set as yearTarget
	print("\n\n\nThank you for using z1883490.awk program!!!\nHere are the outputs\n\nCompany: No-op Computing")
	
	printf("%-20s\t%-15s\t%12s\n","Name", "Position", "Sales Amount" )
	
	# This block of code is use for formatting
	i = 0
	for ( i = 0; i <= 51; i++)
	{
		printf("=")
	}
	#new line
	printf("\n")
	#this counts how many names were counted
	countName=0
}
(NF == 3){ #if the fields have 3, then we will go into this
	#This will get the Pid
	#saves the position for the name
	Pid[$1] = $1
	Position[$1] = $3
	
	#for formatting to make it look nice, this block of code just splits
	#up the name with white-space at the deliumen and re-arranges it so 
	#the last name is first and the first name is last
	split($2,tempName," ")
	name[$1]= tempName[2] ", " tempName[1]
	
	#counts 1 up
	countName++
}
(NF == 4){
	#we are getting the price
	price[$1] = $4
}
(NF == 5){
	#This is very important as we WANT THE 2018 and not any other like
	#2017, 2016, nor 2015. We just want 2018
	split($4,tempDate,"/")
	
	#so, if the tempDate is 2018 (or whatever current year we want) then
	# we will go into this if statement. If it is not 2018, then we ditch it
	if(tempDate[3] == yearTarget)
	{	
		#This right here will take equal to total Sold to how many quanitiy was sold
		#and times it by the price
		totalSold[$5] = totalSold[$5] + ($3 * price[$2]) 
	}
}
END{
	#starting at 1 since it how you do it
	#we will go through each array and then print it out to a pipe |.
	#then i increments by 1 and loops back
	i = 1
		while (i <= countName){
		printf("%-20s\t%-15s\t%12.2f\n", name[i], Position[i], totalSold[i]) | "sort -k 4 -nr"
		i++
	}
}
