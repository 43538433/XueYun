package com.xueyun.www.dao;


import com.xueyun.www.po.User;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;

public interface IUserDao {
    //添加用户
    @Insert("INSERT INTO tb_user VALUES(NULL,#{name},#{password},#{tel},#{sid},#{colloge},#{grade})")
    void insert(User user);

    //根据工学号查找用户,用于在注册时查找用户是否存在
    @Select("SELECT *FROM tb_user WHERE sid=#{sid}")
    User findByUserName(String username);
}
