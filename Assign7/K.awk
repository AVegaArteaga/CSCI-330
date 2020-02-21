#!/bin/awk

BEGIN {
    FS = ":"
    printf("%-17s\t%-9s\t%13s\n", "Name", "Position", "Sales Amount")
    printf("=====================================================\n")
}

NF==4 {
    prod_cat[$1] = $2
    prod_desc[$1] = $3
    prod_price[$1] = $4
}

NF==3 {
    split($2, name, " ")
    associate_name[$1] = name[2] ", " name[1]
    associate_pos[$1] = $3
    associate_total_sale[$1] = 0.0
}

NF==5 {
    sales_date[$1] = $4

    associate_total_sale[$5] += prod_price[$2] * $3 
}

END {
    for (i in associate_total_sale) {
        printf("%-17s\t%-9s\t%13.2f\n", associate_name[i], associate_pos[i], associate_total_sale[i]) | "sort -nr -k4"
    }
}
