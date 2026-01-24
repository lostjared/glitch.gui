#!/usr/bin/perl -w
# perl script to generate Makefile from directories

my $input = ".";
opendir $dir, $input || die("could not open directory");
my @files = readdir $dir;
closedir $dir;
open(HANDLE, '>', "Makefile") or die $!;
print HANDLE "all:\n";
foreach my $fi (sort @files) {
    if ($fi ne "." && $fi ne ".." && $fi ne "plugins") {
    	print HANDLE "\tmake -C " . $fi . "\n" if -d $fi;
    }
}
print HANDLE "install:\n\tcp -rf */*.acidcam ../../../glitch.gui/plugins/\n";
print HANDLE "clean:\n\t rm -rf */*.acidcam";
close(HANDLE);
