import java.sql.*;
import java.util.*;

public class SearchFriend {
	private String username;
	private String password;
	private String friend_name;
	private ArrayList<String> experience = new ArrayList<String>();
	private ArrayList<String> hobby = new ArrayList<String>();
	private ArrayList<String> friendstate = new ArrayList<String>();
	public void setUsername(String username){
		this.username = new String(username);
	}
	public void setPassword(String password){
		this.password = new String(password);
	}
	public void setFriend_name(String friend_name){
		this.friend_name = new String(friend_name);
	}
	public String getUsername(){
		return username;
	}
	public String getPassword(){
		return password;
	}
	public ArrayList<String> getExperience(){
		return experience;
	}
	public ArrayList<String> getHobby(){
		return hobby;
	}
	public ArrayList<String> getFriendstate(){
		return friendstate;
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
			String sql4 = "select * from experience";
			st = (Statement)con.createStatement();
			ResultSet res = st.executeQuery(sql4);
		//	System.out.println("friend_name="+friend_name+" helo");
		//	System.out.println("55555555555");
			while(res.next()){
			//	System.out.println(res.getString("username"));
				if(friend_name.equals(res.getString("username")))
					experience.add(new String(res.getString("degree"))+" graduated from " + new String(res.getString("school")) + " now working at "+new String(res.getString("working_place")));
			}
		//	System.out.println("66666666666");
			String sql5 = "select * from hobbies";
			res = st.executeQuery(sql5);
			while(res.next()){
		//		System.out.println(res.getString("username"));
				if(friend_name.equals(res.getString("username")))
					hobby.add(new String(res.getString("hobby")));
			}
			/*
			 ²é¿´ºÃÓÑµÄ×´Ì¬ºÍ»Ø¸´(Òþ²Ø×´Ì¬±àºÅ)
			create view friendSta as
				select friend.username,content,relpy_name,reply_content
				from friend natural join state,reply
				group by friend.username;
			*/
			String sql6 = "select * from friendSta";
			res = st.executeQuery(sql6);
			while(res.next()){
			//	System.out.println(res.getString("username"));
				String temp = new String(res.getString("content"))+" reply by "+new String(res.getString("relpy_name"))+" is "+new String(res.getString("reply_content"));
				if(friend_name.equals(res.getString("username"))){
				//	System.out.println(temp);
					friendstate.add(temp);
				}
			}
			con.close();
		//	System.out.println("77777777777");
			return "Success";
		}catch(Exception e){
		//	System.out.println("Errors."+e.getMessage());
			return "Failed";
		}
	}
}
