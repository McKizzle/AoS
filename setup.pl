use strict;
use warnings;
use Getopt::Long;
use Cwd 'abs_path';

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
    my $WORKING_DIR = abs_path($0);
    my $HOME = $ENV{"HOME"};  

    my @result = `sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test`;
    @result = `sudo add-apt-repository -y ppa:zoogie/sdl2-snapshots`;
    @result = `sudo apt-get update -y -qq`;
    @result = `sudo apt-get install -qq -y g++-4.8`;
    @result = `sudo apt-get install -qq -y libsdl2-dev`;
    @result = `sudo apt-get install -qq -y libasound2-dev`;
    @result = `sudo apt-get install -qq -y libxss-dev`;
    @result = `sudo apt-get install -qq -y libxxf86vm-dev`;
    @result = `sudo apt-get install -qq -y libpulse-dev`;
    @result = `sudo apt-get install -qq -y git`;
    @result = `sudo apt-get install -qq -y scons`;
    @result = `sudo apt-get install -qq -y wget`;
    
    @result = `wget https://github.com/imvu/gmtl/archive/master.zip -O $HOME/gmtl.zip`;
    @result = `unzip $HOME/gmtl.zip`;
    chdir "$HOME/gmtl-master/";
    @result = `sudo scons install`;
    chdir $WORKING_DIR;

    return @result;
}

sub ubuntu
{
    return 0;
}

