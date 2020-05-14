package com.xueyun.www.po;
/*
老师时间类
 */
public class Time {
    //成员变量
    private String name;    //姓名
    private String sid;     //学号
    private String colloge;   //学院
    private String time;      //时间

    public Time(){}

    public Time(String name, String sid, String colloge, String time){
        this.name=name;
        this.sid=sid;
        this.colloge=colloge;
        this.time=time;
    }

    @Override
    public String toString() {
        return "Time{" +
                ", name='" + name + '\'' +
                ", sid='" + sid + '\'' +
                ", colloge='" + colloge + '\'' +
                ", time='" + time + '\'' +
                '}';
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
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

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }
}
