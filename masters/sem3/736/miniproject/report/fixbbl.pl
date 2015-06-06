chop;

if (/\%$/) {
    s/%$//; print;
} else {
    print "$_\n";
}

