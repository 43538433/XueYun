package com.xueyun.www.dao;

import com.xueyun.www.po.Time;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class TimeDao {
    public List readFist(){
        List<Time> list=new ArrayList<Time>();
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
            String sql="select * from tb_time";
            psmt=connection.prepareStatement(sql);
            rs=psmt.executeQuery();

            while (rs.next()){
                String name=rs.getString("name");
                String sid=rs.getString("sid");
                String colloge=rs.getString("colloge");
                String time=rs.getString("time");
                Time time02=new Time(name,sid,colloge,time);
                list.add(time02);
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
