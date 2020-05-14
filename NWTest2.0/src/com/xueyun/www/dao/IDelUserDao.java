package com.xueyun.www.dao;


import com.xueyun.www.po.User;
import org.apache.ibatis.annotations.Delete;

public interface IDelUserDao {
    //添加用户
    @Delete("delete from tb_user where sid=#{sid}")
    boolean delByUserName(String sid);
}
