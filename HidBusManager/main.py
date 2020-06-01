import sys


def main():
	if ( "-h" in sys.argv[1] ) or ( "--help" in sys.argv[1] ) or ( len(sys.argv) == 1 ):
		print("Usage: HidBusTester [options]");
		print("options:");
		print("\t-h || --help\t\t\tdisplay help and exit");
		print("\t-p <file name>\t\t\tunit to write data");
		print("\t--file\t\t\t\tfile with data to send");
		print("\t--data\t\t\t\tdata to send");
		print("\t--cmdsfile <filename>\t\tfile with commands");
		print("\t-I\t\t\t\tstart interactive mode");


if __name__ == '__main__':
	main()