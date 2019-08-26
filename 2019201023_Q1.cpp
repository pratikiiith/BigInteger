#include<iostream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;


int min(int a,int b){
  return a<b?a:b;
}

bool operator >(vector<int> a , vector<int> b)
{
	if(a.size()!=b.size()) return(a.size()>b.size());
	for(int i=a.size()-1;i>=0;i++)
	{
		if(a[i] == b[i]) continue;
		else return(a[i] > b[i]); 
	}
	return false;
}

bool operator ==(vector<int> a , vector<int> b)
{ 
  while(a.back() == 0 && a.size() > 1) a.pop_back();
  while(b.back() == 0 && b.size()>1) b.pop_back(); 
  // cout << "hi";
  // for(int i=a.size()-1;i>=0;i--){
  //   cout << a[i];
  // }
  if(a.size() != b.size()) return false;
  for(int i=0;i<a.size();i++)
  {
    if(a[i] != b[i]) return false;
  }
  return true;
}


bool operator !=(vector<int> a , vector<int> b)
  {
   while(a.back() == 0 && a.size() > 1) a.pop_back();
  while(b.back() == 0 && b.size()>1) b.pop_back();
    if(a.size() != b.size()) return true;
  for(int i=0;i<a.size();i++)
  {
    if(a[i] != b[i]) return true;
  }
  return false;
}


vector<int> biginteger(string s){
	vector<int> result;
	result.resize(0);
	if(s.size() > 0) {
		while (s.size()%9 != 0) s = '0'+s;
    	for (int i=0;i<s.size();i= i+9) {
        	int a = 0;
        	for (int j=i;j<i+9;j++)
        		{
        			a = a*10 + (s[j]-'0');
        		}
        		result.insert(result.begin(),a);
			}
	}
	else result.push_back(0);
	return result;
}


string add(vector<int> &a, vector<int> &b) {
 
    vector<int> result; 
    int carry = 0;
    int m = min(a.size(),b.size());
    int i;
    for(i=0;i<=m-1;i++){ 
        int sum = 0;
        if (i < a.size()) sum = sum + carry + a[i];
        if (i < b.size()) sum = sum + carry + b[i];
        result.push_back(sum%1000000000);
        carry = sum / 1000000000;
    }

    while (carry && i<a.size()) {
        carry = carry + a[i];
        result.push_back(carry%1000000000);
        carry = carry/1000000000;
        i++;}

    while (carry && i<b.size()) {
        carry = carry + b[i];
        result.push_back(carry%1000000000);
        carry = carry/1000000000;
        i++;}
    if (carry) result.push_back(carry);
    
    while(result.size()>1 && result.back()==0) result.pop_back();
    stringstream ss;
    string temp;
    ss << int(result.back());
    for(int i=result.size()-2;i>=0;i--){
      ss << setw(9) << setfill('0') << result[i];
    }
    ss >> temp;
    return temp;    
    
  }

string sub(vector<int> a, vector<int> b)
{
  vector<int> result;
  int borrow=0;
  for(int i=0;i<a.size();i++)
  {

    borrow = i < b.size() ? borrow+a[i]-b[i]:a[i]+borrow;
    if(borrow<0){
      result.push_back(borrow + 1000000000);

      borrow = -1;
    }
    else{
      result.push_back(borrow);
      borrow=0;
    }

  }

  stringstream ss;
  
  while(result.back()==0) result.pop_back();

    for(int i=result.size()-1;i>=0;i--){
      if(result[i] == 0) { ss << setw(9) << setfill('0') << result[i] << endl;
      }
      else ss << result[i];
    }
    string temp;
    ss >> temp;
    if(temp.size()==0) return "0";
   return temp;

    }

string mul(vector<int> a, vector<int> b) {
    
    if(a.back() == 0) a.pop_back();
    long long len = a.size() + b.size();
    vector<int> result(len,0);

    for(int i=0;i <=a.size()-1;i++) {
        long long carry = 0LL;
        int j=0;
        for (j;j<b.size() || carry > 0;j++) {
            long long mul = j<b.size()?(long long)a[i]*((long long)b[j]):(long long)a[i]*0LL;
           long long s = result[i+j] + carry + mul;
            result[i+j] = s%1000000000;
            carry = s/1000000000;
        }

        while(carry){
          long long s = result[i+j] + carry;
          result[i+j] = s%1000000000;
          carry = s/1000000000;
          j++;
        }
    }
    while(result.size() > 1 && result[result.size()-1] == 0) result.pop_back();
    stringstream ss;
    ss << int(result.back());
    for(int i=result.size()-2;i>=0;i--){
      ss << setw(9) << setfill('0') << result[i];
    }
    string temp;
    ss >> temp;
    return temp;
}


void fact(int n){

  if(n<12){
    int i=1;
    while(n){
      i = i*n;
      n=n-1;
    }
    cout << i << endl;
  }
  string result = "479001600";
  int i = 13;
  while(i<=n){
    stringstream ss;
    string temp;
    ss << i;
    ss >> temp;
    result = mul(biginteger(result), biginteger(temp));
    i++;
  }
  cout << result ;
}

string div(vector<int> a, int b) {
  
    long long  cur = 0LL;
    vector<int> result;
    
    for(int i=a.size()-1;i>=0;i--) {
        cur = (cur*(long long)1000000000 + (long long)a[i]);
        result.insert(result.begin(),cur/b);
        cur %= b;
    }
    stringstream ss;
    if(result[result.size()-1] == 0) result.pop_back();

    for(int i=result.size()-1;i>=0;i--){
      if(result[i] == 0) { ss << setw(9) << setfill('0') << result[i] << endl;
      }
      else ss << result[i];
    }
    string temp;
    ss >> temp;
    if(temp.size()==0) return "0";
   return temp;
}


int mod(vector<int> a, int b) {

    if (b == 0) return -1;
    int result = 0;
    for(int i=a.size()-1;i>=0;i--){
    	result = (result*(1000000000%b) + a[i]%b)%b; }
    return result;
}

vector<int> pow(vector<int> &A, vector<int> &B){
      
      vector<int> zero = biginteger("000");
      if(B == zero) return {1};
    
       vector<int> multiple = biginteger(mul(A,A));
       vector<int> divi = biginteger(div(B,2));

      if(mod(B,2) == 0){
      return pow(multiple,divi);
      }
      else return biginteger(mul(pow(multiple,divi),A));
}

string power(string a,string b)
{
    stringstream ss;
    
    if(a[0] == '-'){
    
      if(b[0] == '+' || b[0]== '-') b[0] = '0';
      vector<int> c = biginteger(b);
      if(mod(c,2) != 0) ss << "-";  
    }

    if(a[0] == '+' || a[0]== '-') a[0] = '0';
    if(b[0] == '+' || b[0]== '-') b[0] = '0';
    
    vector<int> B = biginteger(b);
    vector<int> A = biginteger(a);
    vector<int> result = pow(A,B);
    
    while(result.size() > 1 && result[result.size()-1] == 0) result.pop_back();
   
    ss << int(result.back());
    for(int i=result.size()-2;i>=0;i--){
      ss << setw(9) << setfill('0') << result[i];
    }
    string temp;
    ss >> temp;
    return temp;
}

string gcd2(string a,string b){

	int asize = a.length();
	int bsize = b.length();
	
    while(asize != bsize+1){
    	string temp = b;
    
    	if(a[0] > b[0]){
    		stringstream ss;
    		ss << left << setw(asize-bsize) << setfill('0') << temp << endl;
    		string t;
    		ss >> t;
    		a =	sub(biginteger(a),biginteger(t));
    		asize = a.length();
    	}
    	else{
    		stringstream ss;
    		ss << left << setw(asize-bsize-1) << setfill('0') << temp << endl;
    		string t;
    		ss >> t;
    		a =	sub(biginteger(a),biginteger(t));
    		asize = a.length();
    	}

    }
    return a;

}

string gcd(string a, string b){

    if(a[0] == '+' || a[0]== '-') a[0] = '0';
    if(b[0] == '+' || b[0]== '-') b[0] = '0';
    a = gcd2(a,b);
    vector<int> A = biginteger(a);
    vector<int> B= biginteger(b);
    vector<int> zero = biginteger("000");
   // cout << "hi";

   if( A == zero) return b;
      while(B != zero){
        if(A == B) {

          stringstream ss;
          if(A[A.size()-1] == 0) A.pop_back();

          for(int i=A.size()-1;i>=0;i--){
          if(A[i] == 0) { ss << setw(9) << setfill('0') << A[i] << endl;
                    }
          else ss << A[i];
          }
          string temp;
          ss >> temp;
          if(temp.size()==0) return "0";
            return temp;
        }

        else if(A > B){
          string temp = sub(A,B);
          A = biginteger(temp);
        }
        else{
          string temp = sub(B,A);
          B=biginteger(temp);
        }
      }
      stringstream ss;
      if(A[A.size()-1] == 0) A.pop_back();

      for(int i=A.size()-1;i>=0;i--){
        if(A[i] == 0) { ss << setw(9) << setfill('0') << A[i] << endl;
      }
      else ss << A[i];
      }
      string temp;
      ss >> temp;
      if(temp.size()==0) return "0";
    return temp;
    //return A;
}



void operator +(string a,string b){
  if(a[0] == '-' && b[0] == '-'){

      a[0] = '0';
      b[0] = '0';
      vector<int> A = biginteger(a);
      vector<int> B = biginteger(b);
      cout << '-';
      cout << add(A,B) << endl;

  }
  else if(a[0] == '-' && b[0] != '-'){
        a[0] = '0';
        if(b[0] == '+') b[0] = '0';
        vector<int> A = biginteger(a);
         vector<int> B = biginteger(b);
        if(A>B) {
         // cout << A.size() << " " << B.size()<<endl;
            cout << '-';
            cout << sub(A,B);
          }
        else{
          cout << sub(B,A);
          }
      }
  else if(a[0] != '-' && b[0] == '-'){
        b+a;  }

  else{
    if(a[0] == '+') a[0] = '0';
    if(b[0] == '+') b[0] = '0';
     vector<int> A = biginteger(a);
      vector<int> B = biginteger(b);
      cout << add(A,B) << endl;
  }
  
}

void operator -(string a,string b){

  if(a[0] == '-' && b[0] == '-'){
    b[0] = '0';
    a+b ;
  }
  else if(a[0] == '-' && b[0] != '-'){
    a[0] = '0';
    if(b[0] == '+') b[0] = '0';
    vector<int> A = biginteger(a);
    vector<int> B = biginteger(b);
    cout << "-";
    cout << add(A,B);
    
  }
  else if(a[0] != '-' && b[0] == '-'){
    b[0] = '0';
    if(a[0] == '+') a[0] = '0';
    vector<int> A = biginteger(a);
    vector<int> B = biginteger(b);
    cout << add(A,B);
  }
  else{
    if(b[0] == '+') b[0] = '0';
    if(a[0] == '+') a[0] = '0';
     vector<int> A = biginteger(a);
    vector<int> B = biginteger(b);

    if(A==B) cout << 0;
    else if(A>B) cout << sub(A,B) <<  endl;
    else{
      cout << "-";

      cout << sub(B,A) << endl;
    }

  }

}


void operator *(string a,string b){
  
  if(a[0] == '-' && b[0] == '-'){
    
    a[0] = '0';
    b[0] = '0';
    vector<int> A = biginteger(a);
     vector<int> B = biginteger(b);
    cout << mul(A,B) << endl;
  }
  else if(a[0] == '-' && b[0] != '-'){
     
      a[0] = '0';
      if(b[0] = '+') b[0] = '0';
      vector<int> A = biginteger(a);
      vector<int> B = biginteger(b);
      cout << "-";
      cout << mul(A,B) << endl;
    }
  else if(a[0] != '-' && b[0] == '-'){
        b*a;}
    else{
       if(b[0] == '+') b[0] = '0';
        if(a[0] == '+') a[0] = '0';
        vector<int> A = biginteger(a);
        vector<int> B = biginteger(b);
        cout << mul(A,B) << endl;
    }
  
}

void operator /(string a,string b){
  vector<int> A = biginteger(a);
  stringstream ss;
  ss << b;
  int B=0;
  ss >> B;
  cout << div(A,B) << endl;
}


void operator %(string a,string b){
  vector<int> A = biginteger(a);
  stringstream ss;
  ss << b;
  int B=0;
  ss >> B;
  cout << mod(A,B) << endl;
}


int main()
{

    int n;
    cin >> n;
    string a,b,c,d;
    int e;
    switch(n){
      case 1: 
        cin >> a;
        cin >> b;
        cout << power(a,b) << endl;
        break;

      case 2:
        cin >> c;
        cin >> d;
        cout << gcd(c,d) << endl;
        break;

      case 3:
        cin >> e;
        fact(e);
        break;
    }
    // string a = "12";
    // string b= "-12";
    // a-b;
    // a-b;
    // a*b; 
    // a/b; //bigint and int
    // a%b;
    //fact(10000);
    // cout << endl;
   // cout << power("100000000000000000000","12345") << endl;
   // cout << gcd("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999888888888888888888888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998","1") << endl;
 
  return 0;
}
