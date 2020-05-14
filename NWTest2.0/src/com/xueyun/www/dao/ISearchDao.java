package com.xueyun.www.dao;


import com.xueyun.www.po.Time;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;

public interface ISearchDao {
    //根据老师姓名查询
    @Select("SELECT * FROM tb_time WHERE name=#{name}")
    Time findByUserName(@Param("name")String name);
}
