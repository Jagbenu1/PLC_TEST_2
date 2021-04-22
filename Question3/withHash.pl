$number = 0;
$range_of_rand = 4009;
%value;
$digits = 100;
$range = 100;

while($number < $range){
    $key = int(rand($range_of_rand));
    $value{''.($key%$digits)} = $key;
    print %value{$key};
    print "\n"."Hello World!".$number."\n";
    $number = $number + 1;
}

print %value;
