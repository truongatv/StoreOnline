struct other_info{
	char* email;	//mail
	char* full_name; // ten
	char* address; //dia chi
	char* phone_number; // sdt
};
struct item
 {
 	/* data */
 	char* item_name; // ten
 	char* bio;	//mo ta
 	char* price; //gia
 	char* total; //so luong hien co
 }; 
 struct item_list
 {
 	/* data */
 	struct item item;  
 	struct item_list* next;
 };

struct account{
	char* username;
	char* passwd;
	struct other_info *other_info;
	struct item_list *cart; //gio hang
	struct item_list *favorite_list; //mat hang yeu thich
};
/*
100-login;
101-signup;
102-logout;
999-exit;
888-ready;
103-notmatch userid
104-acc is offline
105-acc is online
106-account already exist
107-send passwd
108-not match pass
109-match pass authenticated
110-send passM to create new acc
111-retry over 5 times

501- client send item_name to server
502- not found item
503- found item
504- client ready to recv item_info

700 - client send request to get favorite list
701 - customer doesn't have any favorite item
702 - customer has favorite item

*/
**menu 1
1. Dang Nhap
2. Tao tai khoan moi
3. Ket thuc

** menu 2
Tai khoan: 	1. Sua chua thong tin
			2. Dang Xuat
Hoat Dong: 	3.Tim kiem mat hang
			4. Kiem tra don hang
			5. Mat hang yeu thich
			6. Kiem tra gio hang
			7. Mua hang

** tim kiem mat hang
phia client:
- gui request_code = 501
- nhan ve result_code
	kiem tra result_code == 888 thi tiep tuc
- gui item_name
- nhan ve result_code
	kiem tra result_code == 502 => khong co mat hang nay, ket thuc
	kiem tra result_code == 503 => co mat hang nay, gui request_code == 504, san sang nhan thong tin sp 
- nhan thong tin san pham, show ra console, ket thuc

phia server
- nhan request_code
	kiem tra request_code == 501 thi send 888 va tiep tuc
- nhan item_name
	kiem tra item_name co trong csdl khong
		khong co thi gui ve result_code == 502, ket thuc
		co thi gui ve result_code == 503, tiep tuc
- nhan request_code == 504
- gui lai thong tin ve san pham, ket thuc

** mat hang yeu thich
phia client:
- gui request_code = 700
- nhan ve result_code == 888 thi tiep tuc
- gui username cua acc hien tai tren client
- nhan ve result_code
	kiem tra result_code == 701 => acc gui len khong co mat hang yeu thich nao, in ra thong bao trn console, ket thuc
	kiem tra result_code == 702 => co mat hang yeu thich, gui lai result_code == 888, tiep tuc
- nhan ve struct item_list, chinh la thong tin ve cac mat hang yeu thich, show ra console, ket thuc

phia server
- nhan request_code
	kiem tra request_code == 700 thi send 888 va tiep tuc
- nhan user_name
	tim kiem user_name, tra ve account co user_name do, kiem tra favorite_list cua account 
		neu khong co favorite_list, gui ve result_code == 701, ket thuc
		neu co favorite_list, gui ve 702, tiep tuc
- nhan request_code == 888, tiep tuc
- gui ve favorite_list vua tim duoc, ket thuc

** gio hang
phia client
- gui request_code == 800
- nhan ve result_code  == 888 thi tiep tuc
- gui user_name cua acc hien tai tren client
- nhan ve result_code
	kiem tra result_code == 801 => khong co gi trong gio hang, in ra thong bao, ket thuc
	kiem tra result_code == 802 => co do` trong gio hang, gui lai request_code == 888, tiep tuc
- nhan ve struct item_list, chinh la thong tin ve cac san pham trong gio hang, in ra console, ket thuc

phia server
- nhan request_code == 800 thi tiep tuc
- gui lai result_code == 888
- nhan user_name
	tim kiem user_name, tra ve account co user_name, kiem tra cart cua account
		neu khong co cart, gui ve request_code == 801, ket thuc
		neu co cart, gui ve 802, tiep tuc
- nhan ve request_code == 888, tiep tuc
- gui ve cart vua tim duoc, ket thuc

** mua hang
phia client
- gui request_code == 900
- nhan ve result_code == 888 thi tiep tuc
- gui user_name cua acc hien tai tren client
- nhan ve gia tien, in ra console

phia server
-nhan request_code == 900
- gui lai result_code == 888
- nhan user_name, tim kiem account chua user_name, lay ra cart cua account, tinh tong so tien (total_pay) trong danh sach cart
	neu cart rong thi gui total_pay = 0
- gui ve total_pay , ket thuc

** sua chua thong tin
phia client
- gui request_code == 300
- nhan ve result_code == 888 thi tiep tuc
- co the thay doi pass, other_info
- gui bien struct account len cho server
- nhan ve result_code == "OK" thi ket thuc

phia server
- nhan request_code == 300 thi tiep tuc
- gui ve result_code == 888
- nhan bien struct account
	tim kiem trong account list theo user_name, thay doi cac thong tin nhu passwd va other_info
- ket thuc, gui ve result_code =="OK"

** login 
phia client
- gui request_code == 100
- nhan ve result_code == 888 thi tiep tuc
