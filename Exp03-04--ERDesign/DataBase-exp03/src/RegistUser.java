import java.sql.*;
import java.util.*;

import javax.resource.cci.ResultSet;

public class RegistUser {
	private String username;
	private String sex;
	private String birthday;
	private String address;
	private String password;
	
	public void setUsername(String username){
		this.username = new String(username);
	}
	public void setSex(String sex){
		this.sex = new String(sex);
	}
	public void setBirthday(String birthday){
		this.birthday = new String(birthday);
	}
	public void setAddress(String address){
		this.address = new String(address);
	}
	public void setPassword(String password){
		this.password = new String(password);
	}
	
	Connection con;
	Statement st;
	public static Connection getConnection(){
		Connection con = null;
		try{
			Class.forName("com.mysql.jdbc.Driver");
			con = DriverManager.getConnection("jdbc:mysql://localhost:3306/social","root","agao0930yjc");
		}catch(Exception e){
			System.out.println("Connect Fail:"+e.getMessage());
		}
		return con;
	}
	
	public String execute() throws Exception{
		con = getConnection();
		try{
			/*
			String sql1 = "select * from user";
			ResultSet res = st.executeQuery(sql1);
			while(res.next()){
				if(username.equals(res.getString("username")))
					return "Failed";
			}
			*/
			if(username==null)
				return "Failed";
			String sql = "INSERT INTO user(username,sex,birthday,address,password)"+"VALUES("+"'"+username+"','"+sex+"','"+birthday+"','"+address+"','"+password+"')";	
			st = (Statement)con.createStatement();
			int count = st.executeUpdate(sql);
		//	System.out.println("Insert Successful.DataNum:"+count);
			con.close();
			return "Success";
		}catch(SQLException e){
			return "Failed";
		}
	}
}