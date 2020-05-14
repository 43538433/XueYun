package com.xueyun.www.util;
/*
数据库连接和关闭
 */
import java.sql.Connection;
import java.sql.DriverManager;

public class DBUtils {
    final static String DRIVER="com.mysql.jdbc.Driver";//数据库驱动字符串
    final static String URL="jdbc:mysql://localhost:3306/nwtest03?characterEncoding=utf-8&useSSL=false";
    final static String USER="root";//数据库用户名
    final static String PASSWORD="root";//数据库密码

    public static Connection getConnection(){
        try{
            Class.forName(DRIVER);
            Connection connection= DriverManager.getConnection(URL,USER,PASSWORD);
            //System.out.println("连接成功！");
            return connection;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static void closeConnection(Connection con){
        try {
            con.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
