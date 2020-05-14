package com.xueyun.www.service;

import com.xueyun.www.dao.IDelUserDao;
import com.xueyun.www.dao.ISearchDao;
import com.xueyun.www.dao.ITimeDao;
import com.xueyun.www.dao.IUserDao;
import com.xueyun.www.po.Time;
import com.xueyun.www.po.User;
import com.xueyun.www.exception.CustomerErrorMsgException;
import com.xueyun.www.util.Md5Util;
import com.xueyun.www.util.MybatisUtils;
import org.apache.ibatis.session.SqlSession;

import java.util.List;

/**
 * @author 黑马程序员
 */
public class UserService {

    //实现业务用户注册方法
    public boolean register(User user)throws Exception{

        //初始化资源
        SqlSession sqlSession = MybatisUtils.getSession();
        //获取接口映射对象
        IUserDao userDao = sqlSession.getMapper(IUserDao.class);

        //1.校验用户名是否被注册,调用dao根据用户名查找用户对象
        User dbUser = userDao.findByUserName(user.getSid());

        //用户对象如果不为空，说明用户名已被注册，校验不通过
        if(dbUser!=null) {
            //2.校验不通过抛出自定义异常实现
            //return false; 这个只能说明注册失败，没有失败的原因
            //如何既能结束应用程序返回又可以给出失败的原因消息？
            //答:抛出异常
            //异常使用原则：
            //  1.抛出系统异常（Exception,RuntimeException...）,  前端要提示友好信息“服务器忙。。。”
            //  2.抛出自定义异常，让用户去解决这个问题，不弹出服务器忙
            throw  new CustomerErrorMsgException("该账号已被注册");
        }

        //3.对密码加密（为了防止数据库管理员泄密）
        /*
         * 【为什么要加密？】
         * 答：所有企业数据的泄密都是来自于内部数据库管理员，所以对存入数据库的敏感数据需要加密
         *
         * 【使用什么技术加密？】
         * 答：使用 MD5 加密
         *
         * 【MD5 介绍】,消息摘要第 5 版加密算法，号称不可逆的加密。这个算法是标准的，
         * 任何语言都提供了对应的固定算法代码，直接使用工具类获取就可以
         *
         * 【加密算法中有 2 个类型】
         * 单向不可逆加密算法，md5
         * 双向可逆的加密算法，res,sha,rsa 等等
         * 【md5 加密特点】
         * 1.任意长度字符串加密后都会得到一个 32 个长度字符的密文字符串
         * 2.同一个字符串每次使用 md5 加密后得到的都是同一个密文字符串
         *
         *
         * md5不安全：
         *  因为网上有很多md5解密的网站，解密原理：
         *  网站主将所有的字符串进行组合生成md5的密文，将原始数据与密文写入到数据库形成庞大的md5密文库；
         *  用户只需要将密文给到网站主，网站主从数据库操作对应一样的密文，就找到原始数据了；
         *
         * 如何解决MD5不安全？
         *  答：解决方案：加盐加密，会将密码+随机字符串 使用MD5生成密文，这样就是通过密文找到原始数据也不知道密码具体是什么
         * */
        //使用工具类对密码加密
        String md5 = Md5Util.getMD5(user.getPassword());
        //将密文封装到用户user对象中，用于写入数据库
        user.setPassword(md5);

        //4.将用户数据插入数据库
        userDao.insert(user);

        //关闭资源
        MybatisUtils.closeSession(sqlSession);

        return true;
    }

    //实现登录方法
    public User login(String name,String sid ,String password)throws Exception{
        //初始化资源
        SqlSession sqlSession = MybatisUtils.getSession();
        IUserDao userDao = sqlSession.getMapper(IUserDao.class);
        //校验用户名
        User loginUser = userDao.findByUserName(sid);
        //判断用户名是否为空
        if (loginUser==null){
            //结束程序并返回“用户名或密码错误”
            throw new CustomerErrorMsgException("用户名或密码错误");

        }
        //校验密码
        //对用户输入的密码进行加密
        String md5 = Md5Util.getMD5(password);
        //与loginUser里面的密文进行对比
        if (!md5.equals(loginUser.getPassword())){
            //密码错误，返回“用户名或密码错误”
            throw new CustomerErrorMsgException("用户名或密码错误");
        }

        //关闭资源
        MybatisUtils.closeSession(sqlSession);
        //校验成功，返回登录用户数据
        return loginUser;
    }

    //添加时间
    public boolean time(Time time){
        //初始化资源
        SqlSession sqlSession = MybatisUtils.getSession();
        //获取接口映射对象
        ITimeDao timeDao = sqlSession.getMapper(ITimeDao.class);
        //4.将时间数据插入数据库
        timeDao.insert(time);

        //关闭资源
        MybatisUtils.closeSession(sqlSession);
        return true;
    }

    //根据老师的姓名进行查询
    public Time search(String name) throws Exception {
        //初始化资源
        SqlSession sqlSession = MybatisUtils.getSession();
        ISearchDao searchDao = sqlSession.getMapper(ISearchDao.class);
        //查找姓名
        Time timeuser= searchDao.findByUserName(name);

        //判断用户名是否为空
        if (timeuser==null){
            //结束程序并返回“用户名或密码错误”
            throw new CustomerErrorMsgException("输入的数据有误，未查找到该数据！");
        }

        //关闭资源
        MybatisUtils.closeSession(sqlSession);
        //校验成功，返回登录用户数据
        return timeuser;
    }

    public boolean delete(String sid) throws Exception {
        //初始化资源
        SqlSession sqlSession = MybatisUtils.getSession();
        IDelUserDao delUserDao= sqlSession.getMapper(IDelUserDao.class);
        //删除指定姓名
        boolean flag=delUserDao.delByUserName(sid);

        if(!flag){
            //结束程序并返回“该用户不存在”
            throw new CustomerErrorMsgException("用户名或密码错误");
        }
        //关闭资源
        MybatisUtils.closeSession(sqlSession);
        return true;
    }
}
