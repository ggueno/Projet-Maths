#!/usr/bin/perl -w
#***************************************************************************\
# Copyright (C) by University Paris-Est - MISS team
# LIN_makeworld.pl created in 10 2008.
# Mail : biri@univ-mlv.fr
#
# This file is part of the OpenKraken.
#
# The OpenKraken is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# The OpenKraken is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#***************************************************************************/

#
# This little script is used to compile/install/test all  OpenKraken
#

use strict;

#my ($installtype) = @ARGV;
my @installtype = @ARGV;
print "@installtype"."\n";

if ((!$installtype[0])  || !scalar(grep(/^$installtype[0]/, ("build","install","clean","test","doc","all")))) {
    print "usage :  LIN_makeworld.pl build/install/test/clean [lib1 lib2 ...]\n";
    print "      :  where lib1/lib2 ... (optional) are the libraries to build/install/...\n";
    print "      :  if one or more of the following lib is not put in option, they are all done\n";
    print "      :  math/image/util/geometry/controller/vision/opengl/video/morphotopo/cuda\n";
    print "      :  \n";
    print "      :  NB if you use global installation don't forget to use root access\n";
    print "      :     if you use root access some file on your account will be owned by root\n";
    print "      :     use \"sudo chown user:group openKN-wantedlib -R\" in your openkn directory to get your right back\n";
    exit(1);
}

my $root = ".."; #mother of all dir

#Opening root dir
my $rootdir;
opendir($rootdir,$root) or die "Painfully : $root doesn't exists";

#installation order
my @oknlist=("OpenKN-math","OpenKN-image","OpenKN-util","OpenKN-geometry","OpenKN-controller","OpenKN-vision","OpenKN-opengl","OpenKN-video","OpenKN-morphotopo","OpenKN-cuda");

#lib to install
my %liblist;
if($#installtype>0){#if specific lib
  foreach my $libs(@installtype[1,$#installtype]){
    $liblist{"OpenKN-".$libs} = "install";
  }
}else{#else all lib
  while(my $libs = readdir($rootdir)){
    if($libs =~ /^OpenKN-/) { #is it interesting
      $liblist{$libs} = "install";
    }
  }
}

#Foreach lib
my @oknInstall;
foreach my $libs(@oknlist){
  if($liblist{$libs}){
        chdir($rootdir);
		my $libdir;
		print $libs."\n";
		opendir($libdir,$libs) or die "Another day : $libs doesn't exists";

		my $builddir;
		if(!opendir($builddir,$libs."/build")){
			print "Creating ".$libs."/build\n";
			mkdir ($libs."/build");
			opendir($builddir,$libs."/build");
		}
		chdir($builddir) or die "help";

		if(!($installtype[0] eq "clean") || !open(MAKEFILE,"Makefile")){
		open(CMAKE,"cmake .. 2>&1|");
		  while (<CMAKE>){
		    print $_;
		  }
		close(CMAKE);
		}else{
		  close(MAKEFILE);
		}

		if ($installtype[0] eq "all") {
			open(MAKE,"make install 2>&1|");
			while (<MAKE>){
				print $_;
			}
			close(MAKE);
			open(MAKE,"make html 2>&1|");
			while (<MAKE>){
				print $_;
			}
			close(MAKE);
			my $testdir;
			if(opendir($testdir,"../tests")){
				chdir($testdir);
				open(MAKE,"make 2>&1|");
				while (<MAKE>){
					print $_;
				}
				close(MAKE);
			} else {
				print "No tests for $libs?\n";
			}
		}elsif ($installtype[0] eq "install") {
			open(MAKE,"make install 2>&1|");
			while (<MAKE>){
				print $_;
			}
			close(MAKE);
		}elsif ($installtype[0] eq "doc") {
			open(MAKE,"make html 2>&1|");
			while (<MAKE>){
				print $_;
			}
			close(MAKE);
		} elsif ($installtype[0] eq "test") {
			my $testdir;
			if(opendir($testdir,"../tests")){
				chdir($testdir);
				open(MAKE,"make 2>&1|");
				while (<MAKE>){
					print $_;
				}
				close(MAKE);
			} else {
				print "No tests for $libs?\n";
			}
		} elsif ($installtype[0] eq "clean") {
			open(MAKE,"make clean 2>&1|");
			while (<MAKE>){
				print $_;
			}
			close(MAKE);
		}
		else {
			open(MAKE,"make 2>&1|");
			while (<MAKE>){
				print $_;
			}
			close(MAKE);
		}

		closedir($builddir);
		closedir($libdir);
	}
}
