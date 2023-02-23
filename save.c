	case modifier_s:
	    switch (str[i]) {
	    case 'h':
		SUB_1(stage); /*for  Short*/
		break;
	    case 'l':
		ADD_1(stage); /* for Long*/
		break;
	    case 'z':
		stage = F_LONG; /*size_t*/
		break;
	    case 't':
		stage = FL_LONG;
		break;
	    case 'j':
		stage = FL_LONG_LONG; /* ptrdiff_t */
		break;
	    case 'L':
	    case 'q':
		stage = FL_LONG_LONG;
		break;
	    case 'v':
		stage = FL_REV;
	    default:
		if (stage < MIN_S)
		    stage = MIN_S;
		else if (stage > MAX_S)
		    stage = MAX_S;

	        off_fmt= output_mod_s;
		break;
	    }
	    case 'f':
		db_val = db_formt(args, rank);
		break;
	    case 'E':
		UPPER = 1;
	    case 'e':
		db_val = db_formt(args, rank);
		break;
	    case 'G':
		UPPER = 1;
	    case 'g':
		db_val = db_formt(args, rank);
		break;
	    case 'A':
		UPPER = 1;
	    case 'a':
	    case '%':
		PUSH('%', buff, len++);
	    }
	}
	off_fmt = normal_s;
	i++;
    }






	    break;
	}


    buff[len] = '\0';
    while (buff[i]){
	write(1, buff[i], 1);
	i++;
    }
    free(buff);
}

