BEGIN{

# changing field separator to :

FS=":";

# printing the header in output

print "No-op Computing";

print "2013 Sales Associates Ranking";

}

{

# if number of fields is 4, the lines contain product information

if(NF == 4){

p_pid = $1;

p_price = $4;

prod_cost[p_pid] = p_price;

}

# if number of fields is 3, the lines containing employee information

else if(NF == 3){

e_aid = $1;

e_name = $2;

e_pos = $3;

emp[e_aid] = e_name "-" e_pos;

}

# if the number of fields is 5, the linees containg product sales information

else if(NF == 5){

s_pid = $2;

s_quant = $3;

s_date = $4;

s_aid = $5;

# if sales date year is 2013

if(s_date ~ /\/2013/){

# if employees is in sales hash add the product cost to the sales employee did

if (s_aid in sales)

sales[s_aid] = sales[s_aid] + prod_cost[s_pid] * s_quant;

else

sales[s_aid] = prod_cost[s_pid] * s_quant;

}

}

}

END{

printf "%20s %15s %20s\n", "Name", "Position", "Sales Amount";

printf "==========================================================\n";

# printing sales information

for(eid in sales){

if(eid in emp){

split(emp[eid], a, "-");

emp_name = a[1];

position = a[2];

printf "%20s %15s %15.2f\n", emp_name, position, sales[eid];

}

}

}
