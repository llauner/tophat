#!/usr/bin/perl -w

use strict;

sub generate_blob($$) {
    my ($var, $path) = @_;

    print "extern const uint8_t ${var}\[\];\n";
    print "extern const uint8_t ${var}_end\[\];\n";
}

print "#include <stdint.h>\n";

my @numeric;
my @named;

while (<>) {
    # merge adjacent strings
    while (s/"([^"]*)"\s+"([^"]*)"\s*$/"$1$2"/) {}

    if (/^\s*(\d+)\s+BITMAP\s+DISCARDABLE\s+"(.*?)"\s*$/) {
        push @numeric, [ $1, -s "Data/$2" ];
        generate_blob("resource_$1", "Data/$2");
    } elsif (/^\s*([.\w]+)\s+(?:TEXT|XMLDIALOG|MO|RASTERDATA)\s+DISCARDABLE\s+"(.*?)"\s*$/) {
        push @named, [ $1, -s "Data/$2" ];
        my $path = $2;
        my $variable = "resource_$1";
        $variable =~ s,\.,_,g;
        generate_blob($variable, "Data/$path");
    }
}

print "#include \"Util/ConstBuffer.hpp\"\n";
print "#include <tchar.h>\n";

print "static constexpr struct {\n";
print "  unsigned id;\n";
print "  ConstBuffer<void> data;\n";
print "} numeric_resources[] = {";
foreach my $i (@numeric) {
    my ($id, $size) = @$i;
    print "  { ${id}, { resource_${id}, ${size} } },\n";
}
print "  { 0, { nullptr, 0 } }\n";
print "};\n";

print "static constexpr struct {\n";
print "  const TCHAR *name;\n";
print "  ConstBuffer<void> data;\n";
print "} named_resources[] = {";
foreach my $i (@named) {
    my ($name, $size) = @$i;
    my $variable = "resource_${name}";
    $variable =~ s,\.,_,g;
    print "  { _T(\"${name}\"), { ${variable}, ${size} } },\n";
}
print "  { 0, { nullptr, 0 } }\n";
print "};\n";
