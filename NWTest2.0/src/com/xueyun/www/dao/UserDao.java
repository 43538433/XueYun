package com.xueyun.www.dao;

import com.xueyun.www.po.User;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class UserDao {
    public List readFist(){
        List<User> list=new ArrayList<User>();
        Connection connection=null;
        PreparedStatement psmt=null;
        ResultSet rs=null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        try{
            connection= DriverManager.getConnection("jdbc:mysql://localhost:3306/nwtest03?characterEncoding=utf-8&useSSL=false","root","root");
            String sql="select * from tb_user";
            psmt=connection.prepareStatement(sql);
            rs=psmt.executeQuery();

            while (rs.next()){
                String name=rs.getString("name");
                String password=rs.getString("password");
                String tel=rs.getString("tel");
                String sid=rs.getString("sid");
                String colloge=rs.getString("colloge");
                String grade=rs.getString("grade");

                User user=new User(name,password,tel,sid,colloge,grade);
                list.add(user);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            try{
                if(rs!=null){
                    rs.close();
                }
                if(psmt!=null){
                    psmt.close();
                }
                if(connection!=null){
                    connection.close();
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return list;
    }

}
