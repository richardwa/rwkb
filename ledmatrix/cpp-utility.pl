#!/usr/bin/perl
use strict;
#set array separator
$, = ',';
$" = ',';

sub addPrefix {
    my $prefix = shift;
    return map $prefix.$_, @_;
}
sub range {
    my $start = shift;
    my $count = shift;
    my $step = shift;
    return map $start + $_*$step, 0..($count-1);
}
sub def {
    print "#define @_\n";
}
my $ARGSIZE=10;
my $LISTSIZE=20;

# basics
def "EMPTY()";
def "COMMA() ,";
def "PASS(...) __VA_ARGS__";
def "_CONCAT(a,b) a##b";

#List helpers
foreach my $i (1..$LISTSIZE){
    def "SIZE_$i(...) $i";
}
def "_SIZE(@{[addPrefix 'a', 1..$LISTSIZE]},n,...) n";
def "SIZE(...) _SIZE(__VA_ARGS__, @{[reverse (addPrefix 'SIZE_', 1..$LISTSIZE)]}) (__VA_ARGS__)";

foreach my $i (1..$LISTSIZE){
    def "IDX_$i(...) @{[0..($i-1)]}";
}
def "_IDX(@{[addPrefix 'a', 1..$LISTSIZE]},n,...) n";
def "IDX(...) _IDX(__VA_ARGS__, @{[reverse (addPrefix 'IDX_', 1..$LISTSIZE)]}) (__VA_ARGS__ )";
def "IDXNUM(n) _CONCAT(IDX_,n)()";

foreach my $i (1..$LISTSIZE){
    def "REPEAT_$i(x,...) @{[map 'x',0..($i-1)]}";
}
def "_REPEAT(x,@{[addPrefix 'a', 1..$LISTSIZE]},n,...) n";
def "REPEAT(...) _REPEAT(__VA_ARGS__, @{[reverse (addPrefix 'REPEAT_', 1..$LISTSIZE)]}) (__VA_ARGS__ )";
print "\n";
#MAP
def "MAP MAP1";
for (my $i=1;$i<=$ARGSIZE;$i++){
    for(my $j=1;$j<=$LISTSIZE;$j++){
        my @arr1 = addPrefix "a",(1..($i*$j));
        my @arr2 = map [addPrefix "a", range($_,$i,$j)],1..$j;
        def "MAP${i}_$j(f,s,@arr1)".join(" s() ",map {"f(@{$_})"} @arr2);
    }
    def "_MAP${i}(f,s,@{[addPrefix 'a', (1..$i*$LISTSIZE)]},n,...) n";
    my @arr3 = reverse map {my $that=$_;map "MAP${i}_$that",1..$i} 1..$LISTSIZE;
    def "MAP${i}(...) _MAP${i}(__VA_ARGS__,@arr3) (__VA_ARGS__ )";
    print "\n";
}
