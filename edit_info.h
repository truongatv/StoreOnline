void edit_info(){
	int i;
	printf("____________EDIT INFO___________\n");
	printf("1.Doi password\n2.Sua mail\n3.Back to menu\n");
	printf("**********************************\n");
	scanf("%d",&i);
	switch(i){
		case 1:{
			change_pass();
			break;
		}
		case 2:{
			change_mail();
			break;
		}
		case 3:{
			back_menu();
			break;
		}
	}
}