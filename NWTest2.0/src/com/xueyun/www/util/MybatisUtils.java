package com.xueyun.www.util;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.Reader;

public class MybatisUtils {
    private static SqlSessionFactory sqlSessionFactory = null;
    private static ThreadLocal<SqlSession> tl = new ThreadLocal<SqlSession>();
    //初始化 SqlSessionFactory 对象
    static {
        try{
            //1 读取配置文件
            String resource ="sqlMapConfig.xml";
            Reader reader = Resources.getResourceAsReader(resource);
            //*
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(reader );
            //*
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }

    }
	
	//获取 SqlSession对象的静态方法
    public static SqlSession getSession()
    {
        //*
        SqlSession sqlSession = tl.get();
        if (sqlSession == null) {
            sqlSession = sqlSessionFactory.openSession();
            tl.set(sqlSession);
        }
        //*
        return sqlSessionFactory.openSession();
    }
	
    //获取 SqlSession 对象的静态方法
    public static SqlSession  getSession(boolean isAutoCommit)
    {
        return sqlSessionFactory.openSession(isAutoCommit);
    }


    //关闭sqlSession
    public static void closeSession(SqlSession sqlSession){
        sqlSession.commit();
        sqlSession.close();
    }
}
