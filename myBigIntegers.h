#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

class Integer{
    std::string s;
public:
    Integer(){}
    Integer(std::string s){
        this->s = s;
    }
    Integer operator+(Integer);
    Integer operator*(Integer);
    Integer operator-(Integer);
    Integer operator*=(Integer);
    Integer operator+=(Integer);
    Integer operator-=(Integer);
    void operator=(std::string);
    bool operator<(Integer);
    bool operator>(Integer);
    bool operator==(Integer);
    bool operator!=(Integer);
    bool operator<=(Integer);
    bool operator>=(Integer);
    Integer operator++();
    Integer operator++(int);
    Integer operator--();
    Integer operator--(int);
    friend Integer factorial(Integer I);
    friend Integer power(Integer,Integer);

    friend std::ostream & operator<<(std::ostream&, const Integer&);
    friend std::istream & operator>>(std::istream&, Integer&);
private:
    void removeLeadingZeros(std::string &s1, std::string &s2, int &l1, int &l2){
        int i = 0, j = 0;
        while(i < l1 && s1[i] == '0'){
            i++;
        }
        s1 = s1.substr(i), l1 = s1.size();
        while(j < l2 && s2[j] == '0'){
            j++;
        }
        s2 = s2.substr(j), l2 = s2.size();
    }
};

void Integer::operator=(std::string s){
    this->s = s;
}

std::ostream& operator<<(std::ostream &out, const Integer &I){
    out<<I.s;
    return out;
}

std::istream& operator>>(std::istream &in, Integer &I){
    in>>I.s;
    return in;
}

bool Integer::operator<(Integer I){
    int n1 = s.length(), n2 = I.s.length();
    if(n1 == n2){
        for(int i = 0; i < n1; i++){
            if(s[i] < I.s[i]){
                return true;
            }
        }
    }
    return n1 < n2;
}

bool Integer::operator>(Integer I){
    int n1 = s.length(), n2 = I.s.length();
    if(n1 == n2){
        for(int i = 0; i < n1; i++){
            if(s[i] > I.s[i]){
                return true;
            }
        }
    }
    return n1 > n2;
}

bool Integer::operator==(Integer I){
    int n1 = s.length(), n2 = I.s.length();
    if(n1 != n2) return false;
    for(int i = 0; i < n1; i++){
        if(s[i] != I.s[i]){
            return false;
        }
    }
    return true;
}

bool Integer::operator!=(Integer I){
    int n1 = s.length(), n2 = I.s.length();
    if(n1 != n2) return true;
    for(int i = 0; i < n1; i++){
        if(s[i] != I.s[i]){
            return true;
        }
    }
    return false;
}

bool Integer::operator<=(Integer I){
    return (*this == I) || (*this < I);
}

Integer Integer::operator+(Integer I){
    std::string s1 = this->s, s2 = I.s;
    int l1 = s1.size(), l2 = s2.size();
    removeLeadingZeros(s1,s2,l1,l2);
    std::string ans;
    int carry = 0;
    l1--, l2--;
    while(l1 >= 0 || l2 >= 0){
        int sum = l2 < 0 ? s1[l1--] - '0': l1 < 0 ? s2[l2--] - '0': s1[l1--] - '0' + s2[l2--] - '0';
        sum += carry;
        ans += (sum % 10 + '0');
        carry = sum/10;
    }
    if(carry){
        ans += (carry + '0');
    }
    reverse(begin(ans),end(ans));
    return Integer(ans);
}

Integer Integer::operator*(Integer I){
    std::string s1 = this->s, s2 = I.s;
    int l1 = s1.size(), l2 = s2.size();
    removeLeadingZeros(s1,s2,l1,l2);
    std::vector<int> res(l1 + l2);
    for(int i = l1-1; i >= 0; i--){
        for(int j = l2-1; j >= 0; j--){
            int mul = (s1[i] - '0') * (s2[j] - '0');
            int pos1 = i + j, pos2 = i + j + 1;
            int sum = res[pos2] + mul;
            res[pos1] += sum / 10;
            res[pos2] =  sum % 10; 
        }
    }
    std::string ans;
    for(int x : res){
        if(x == 0 && ans.size() == 0) continue;
        else{
            ans += x + '0';
        }
    }
    return ans.size() == 0 ? Integer("0") : Integer(ans);
}

Integer Integer::operator-(Integer I){
    std::string s1 = s, s2 = I.s;
    int sign = 1;
    if(*this < I){
        sign = -1;
        std::swap(s1,s2);
    }
    int n1 = s1.size(), n2 = s2.size();
    std::reverse(s1.begin(),s1.end());
    std::reverse(s2.begin(),s2.end());
    int carry = 0;
    std::string ans;
    for(int i = 0; i < n2; i++){
        int sub = ((s1[i]-'0')-(s2[i]-'0')-carry);
        if(sub < 0){
            sub += 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        ans.push_back(sub + '0');
    }
    for(int i = n2; i < n1; i++){
        int sub = (s1[i]-'0'-carry);
        if(sub < 0){
            sub += 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        ans.push_back(sub + '0');
    }
    while(ans.back() == '0'){
        ans.pop_back();
    }
    if(sign < 0){
        ans.push_back('-');
    }
    std::reverse(ans.begin(),ans.end());
    return Integer(ans);
}

Integer Integer::operator+=(Integer I){
    *this = *this + I;
    return *this;
}

Integer Integer::operator*=(Integer I){
    *this = *this * I;
    return *this;
}

Integer Integer::operator-=(Integer I){
    *this = *this - I;
    return *this;
}

Integer Integer::operator++(int){
    Integer temp = *this;
    (*this) = (*this) + Integer("1");
    return temp;
}

Integer Integer::operator++(){
    (*this) = (*this) + Integer("1");
    return *this;
}

Integer Integer::operator--(int){
    Integer temp = *this;
    (*this) = (*this) - Integer("1");
    return temp;
}

Integer Integer::operator--(){
    (*this) = (*this) - Integer("1");
    return *this;
}

Integer factorial(Integer I){
    if(I == Integer("0")){
        return Integer("1");
    }
    Integer ans("1");
    for(Integer i = Integer("1"); i <= I; i++){
        ans *= i;
    }
    return ans;
}

Integer power(Integer I, Integer n){
    if(n == Integer("0")){
        return Integer("1");
    }
    Integer ans("1");
    for(Integer i = Integer("1"); i <= n; i++){
        ans *= I;
    }
    return ans;
}
