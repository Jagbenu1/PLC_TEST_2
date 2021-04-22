
$number = 0;
$range_of_rand = 4009;
my @value;
$digits = 100;
$range = 100;

while($number < $range){
    $key = int(rand($range_of_rand));
    print $key;
    push(@value, $key);
    # print(@value);
    print "\n"."Hello World!".$number."\n";
    $number = $number + 1;
}
print @value;