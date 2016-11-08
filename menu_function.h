void menu_function(char* user){
	int i;
	printf("___________WELLCOME %s_____________\n",user );
	printf("___________MENU_____________________\n");
	printf("1.Tim kiem\n2.Sua thong tin\n3.Kiem tra trang thai don hang\n
		4.Mat hang yeu thich\n5.Gio hang\n6.Mua hang\n7.Logout\n");
	printf("*************************************\n");
	scanf("%d",&i);
	switch(i){
		case 1:{
			search();
			break;
		}
		case 2:{
			edit_info();
			break;
		}
		case 3:{
			status_cart();
			break;
		}
		case 4:{
			favorite();
			break;
		}
		case 5:{
			cart();
			break;
		}
		case 6:{
			buy();
			break;
		}
		case 7:{
			logout();
			break;
		}
	}
}