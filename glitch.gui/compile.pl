#!/usr/bin/perl
use strict;
use warnings;
use File::Path qw(remove_tree make_path);

# --- Configuration ---
my $repo_url   = "https://github.com/lostjared/glitch.gui.git";
my $repo_dir   = "glitch.gui_new"; # Clones to a fresh folder to avoid conflicts
my $build_dir  = "build";

print "--- Step 1: Cloning Repository ---\n";
if (-d $repo_dir) {
    print "Directory $repo_dir already exists. Updating instead...\n";
    chdir($repo_dir);
    system("git pull");
} else {
    system("git clone $repo_url $repo_dir");
    chdir($repo_dir) or die "Could not enter directory: $!";
}

print "\n--- Step 2: Cleaning Source Path (Removing CMake Ghosts) ---\n";
# This fixes the issue where CMake writes to the examples folder
my @junk_files = qw(examples/CMakeCache.txt examples/Makefile examples/cmake_install.cmake);
foreach my $file (@junk_files) {
    if (-e $file) {
        print "Removing $file...\n";
        unlink($file);
    }
}
remove_tree("examples/CMakeFiles");

print "\n--- Step 3: Configuring Build ---\n";
make_path($build_dir) unless -d $build_dir;
chdir($build_dir);

# We target the examples directory specifically since that's where your CMakeLists is
if (system("cmake ../examples -B .") != 0) {
    die "CMake configuration failed!";
}

print "\n--- Step 4: Compiling ---\n";
my $cores = `nproc` || 4;
chomp($cores);
if (system("make -j$cores") == 0) {
    print "\n--- Build Success! ---\n";
    print "Binaries are located in: $repo_dir/$build_dir\n";
} else {
    print "\nBuild failed. Check for missing dependencies (OpenCV/acidcam).\n";
}
