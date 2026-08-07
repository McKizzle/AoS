use strict;
use warnings;
use Getopt::Long;

my $osx = 0;
my $debian = 0;
my $ubuntu = 0;

GetOptions ("osx" => \$osx, 
            "debian" => \$debian, 
            "ubuntu" => \$ubuntu) 
        or die("Error in command line arguments\n");


print "Please enter your password to install the nessary packages:\n";
if($osx) {
    #osx();
} elsif($debian) {
    debian();
} elsif($ubuntu) {
    #ubuntu();
} else {
    print "Example usage:\n";
    print "\tsetup.py --[osx | debian | ubuntu]\n"
}

sub osx 
{
    
    return 0; 
}

sub debian
{
    my @result = `sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test`;
    @result = `sudo add-apt-repository -y ppa:zoogie/sdl2-snapshots`;
    @result = `sudo apt-get update -y -qq`;
    @result = `sudo apt-get install -qq -y g++-4.8`;
    @result = `sudo apt-get install -qq -y libsdl3-dev`;
    @result = `sudo apt-get install -qq -y libglm-dev`;
    @result = `sudo apt-get install -qq -y wget`;

    return @result;
}

sub ubuntu
{
    my @result = `sudo apt-get update -y -qq`;
    @result = `sudo apt-get install -qq -y g++-4.8`;
    @result = `sudo apt-get install -qq -y libsdl3-dev`;
    @result = `sudo apt-get install -qq -y libglm-dev`;
    @result = `sudo apt-get install -qq -y wget`;

    return @result;
    return 0;
}

