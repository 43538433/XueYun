package com.xueyun.www.po;
/*
注册类
 */
public class User {
    //成员变量
    private String name;        //姓名
    private String password;    //密码
    private String tel;   //手机号码
    private String sid;         //工学号
    private String colloge;     //学院
    private String grade;       //专业

    public User(){ }

    public User(String name, String password, String tel,String sid,String colloge,String grade){
        this.name=name;
        this.password=password;
        this.tel=tel;
        this.sid=sid;
        this.colloge=colloge;
        this.grade=grade;
    }

    @Override
    public String toString() {
        return "User{" +
                ", name='" + name + '\'' +
                ", password='" + password + '\'' +
                ", tel='" + tel + '\'' +
                ", sid='" + sid + '\'' +
                ", colloge='" + colloge + '\'' +
                ", grade='" + grade + '\'' +
                '}';
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getTel() {
        return tel;
    }

    public void setTel(String tel) {
        this.tel = tel;
    }

    public String getSid() {
        return sid;
    }

    public void setSid(String sid) {
        this.sid = sid;
    }

    public String getColloge() {
        return colloge;
    }

    public void setColloge(String colloge) {
        this.colloge = colloge;
    }

    public String getGrade() {
        return grade;
    }

    public void setGrade(String grade) {
        this.grade = grade;
    }
}
