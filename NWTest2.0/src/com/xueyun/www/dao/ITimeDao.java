package com.xueyun.www.dao;


import com.xueyun.www.po.Time;
import org.apache.ibatis.annotations.Insert;

public interface ITimeDao {
    //添加用户
    @Insert("INSERT INTO tb_time VALUES(NULL,#{name},#{sid},#{colloge},#{time})")
    void insert(Time time);
}
