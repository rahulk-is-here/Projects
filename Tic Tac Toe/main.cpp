#include <iostream>
#include<algorithm>
using namespace std;

// TASK 3 - Tic Tac Toe Game
 
char grid[9] = {'1','2','3','4','5','6','7','8','9'};
int turn = 1; // Player 1 or Player 2
/*
Grid:
   1 | 2 | 3
   ---------
   4 | 5 | 6
   ---------
   7 | 8 | 9
*/
void reset_grid(){
	grid[0] = '1';
	grid[1] = '2';
	grid[2] = '3';
	grid[3] = '4';
	grid[4] = '5';
	grid[5] = '6';
	grid[6] = '7';
	grid[7] = '8';
	grid[8] = '9';
}
int check_win(){
	if(grid[0] == grid[1] and grid[1] == grid[2]){
		return 1;
	}else if(grid[3] == grid[4] and grid[4] == grid[5]){
		return 1;
	}else if(grid[6] == grid[7] and grid[7] == grid[8]){
		return 1;
	}else if(grid[0] == grid[3] and grid[3] == grid[6]){
		return 1;
	}else if(grid[1] == grid[4] and grid[4] == grid[7]){
		return 1;
	}else if(grid[2] == grid[5] and grid[5] == grid[8]){
		return 1;
	}else if(grid[0] == grid[4] and grid[4] == grid[8]){
		return 1;
	}else if(grid[2] == grid[4] and grid[4] == grid[6]){
		return 1;
	}else if(grid[0] != '1' and grid[1] != '2' and grid[2] != '3' 
	and grid[3] != '4' and grid[4] != '5' and grid[5] != '6' 
	and grid[6] != '7' and grid[7] != '8' and grid[8] != '9'){
		return 0;
	}
	return -1;
}

void display(){
	cout<<"\n\t"<<grid[0]<<"  |  "<<grid[1]<<"  |  "<<grid[2]<<endl;
	cout<<"\t"<<"-------------"<<endl;
	cout<<"\t"<<grid[3]<<"  |  "<<grid[4]<<"  |  "<<grid[5]<<endl;
	cout<<"\t"<<"-------------"<<endl;
	cout<<"\t"<<grid[6]<<"  |  "<<grid[7]<<"  |  "<<grid[8]<<endl<<endl;
}
int main() {
	system("cls");
	cout<<"\n\tTic Tac Toe\n\n"<<endl;
	cout<<"Player 1 -> X and Player 2 -> O\n"<<endl;
	bool flag = true;
	int count = 1;
	while(flag){
		if(count == 1){
			display();
			count++;
		}
		if(turn == 1){ // for player 1
			cout<<"Player 1(X) Turn: ";
			int c;
			cin>>c;
			if(c < 1 or c > 9){
				cout<<"Invalid Input!"<<endl;
				continue;
			}
			if(grid[c-1] == 'X' or grid[c-1] == 'O'){
				cout<<"Block Already Occupied"<<endl;
				continue;
			}
			grid[c-1] = 'X';
			display();
			if(check_win() == 1){
				cout<<"\nPlayer 1 Wins!!"<<endl;
				turn = 0;
				continue;
			}else if(check_win() == 0){
				cout<<"\nDRAW!!"<<endl;
				turn = 0;
				continue;
			}
			turn = 2;
		}else if(turn == 2){ // for player 2
			cout<<"Player 2(O) Turn: ";
			int c;
			cin>>c;
			if(c < 1 or c > 9){
				cout<<"Invalid Input!"<<endl;
				continue;
			}
			if(grid[c-1] == 'X' or grid[c-1] == 'O'){
				cout<<"Block Already Occupied"<<endl;
				continue;
			}
			grid[c-1] = 'O';
			display();
			if(check_win() == 1){
				cout<<"\nPlayer 2 Wins!!"<<endl;
				turn = 0;
				continue;
			}else if(check_win() == 0){
				cout<<"\nDRAW!!"<<endl;
				turn = 0;
				continue;
			}
			turn = 1;
		}else{ // game end
			reset_grid();
			cout<<"Want to Play Again?(1 or 0): ";
			int choice;
			cin>>choice;
			if(choice==1){
				count = 1;
				turn = 1;
				continue;
			}else if(choice==0){
				flag = false;
			}else{
				cout<<"Invalid Input!"<<endl;
				exit(0);
			}
		}
	}
	cout<<"Thank You For Playing!"<<endl;
	return 0;
}
