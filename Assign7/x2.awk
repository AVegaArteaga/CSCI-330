BEGIN{
	FS=":"
	print
	printf("%-25s\t%-20s\t%12s\n","Name", "Position", "Sales Amount" )
	printf("====================================================================\n")
	count=0
}

(NF == 3){

	id[$1]= $1
	pos[$1]= $3

	split($2, arr, " ")
	Name[id[$1]]= arr[1] ", " arr[2]
	count++
	
}

(NF == 4){

	price[$1] = $4
	
}

(NF == 5){
	sold = $3 * (price[$2])
	salesAmount[$5] += sold
}

END{
	i = 1
	
	while (i <= 8){
		printf("%-25s\t%-20s\t%12.2f\n", Name[i], pos[i], salesAmount[i]) | "sort -k 4 -nr"
		i++
	}
}
