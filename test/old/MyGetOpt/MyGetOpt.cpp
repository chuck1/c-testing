	MyGetOpt::MyGetOpt(): opt(0),optc(0) {}
int MyGetOpt::GetLong (int argc, char **argv, const char *shortopts, const struct option *long_options) {
    opt = new MyOption[argc];
	optc = 0;
	
	int c;
    int digit_optind = 0;
    int aopt = 0, bopt = 0;
    char *copt = 0, *dopt = 0;
	
    //printf("argc %i\n",argc);
	
    int option_index = 0;
    while ( ( c = getopt_long( argc, argv, shortopts, long_options, &option_index ) ) != -1 ) {
		//int this_option_optind = optind ? optind : 1;
		
		
		/*
		printf ("optind %i\n",optind);
		printf ("optarg '%s'\n",optarg);
		*/
		//printf ("optind '%s'\n",optind);
		switch (c) {
		case '?':
			/*printf ("?\n");*/
			
			break;
		default:
			opt[optc++] = {c,optarg};
			
			break;
		}
		
		
		
		/*
		switch (c) {
        case 0:
            printf ("option %s", long_options[option_index].name);
            if (optarg)
                printf (" with arg %s", optarg);
            printf ("\n");
            break;
        case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind)
              printf ("digits occur in two different argv-elements.\n");
            digit_optind = this_option_optind;
            printf ("option %c\n", c);
            break;
        case 'a':
            printf ("option a\n");
            aopt = 1;
            break;
        case 'b':
            printf ("option b\n");
            bopt = 1;
            break;
        case 'c':
            printf ("option c with value '%s'\n", optarg);
            copt = optarg;
            break;
        case 'd':
            printf ("option d with value '%s'\n", optarg);
            dopt = optarg;
            break;
        case '?':
            break;
        default:
            printf ("?? getopt returned character code 0%o ??\n", c);
        }
		*/
		
    }
    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }
	
	
	return 0;
}
int MyGetOpt::Get (int argc, char **argv, const char *shortopts) {
	/*
	int aflag = 0;
	int bflag = 0;
	char *cvalue = NULL;
	*/
	int index;
	int c;
	
	opt = new MyOption[argc];
	optc = 0;
	
	//opterr = 0;
	
	while ((c = getopt (argc, argv, shortopts)) != -1) {
		/*
		printf("c %c\n",c);
		printf("optopt '%c'\n",optopt);
		printf("optarg '%s'\n",optarg);
		*/
		
		switch (c)
		{
		case '?':
			/*
			if (optopt == 'c') {
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			}
			else if (isprint (optopt)) {
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			}
			else {
				fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
				return 1;
			}
			*/
			break;
		default:
			opt[optc++] = {c,optarg};
			//abort ();
			break;
		}
	}
	
	//printf ("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);

	for (index = optind; index < argc; index++) {
		printf ("Non-option argument %s\n", argv[index]);
	}
	
	return 0;
}


