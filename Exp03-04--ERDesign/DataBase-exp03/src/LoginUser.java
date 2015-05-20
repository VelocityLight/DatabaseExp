import java.util.*;
import java.sql.*;

public class LoginUser {
	private String username;
	private String password;
	private ArrayList<String> friendlist = new ArrayList<String>();
	private ArrayList<String> message = new ArrayList<String>();
	private ArrayList<String> experience = new ArrayList<String>();
	private ArrayList<String> hobby = new ArrayList<String>();
	//private ArrayList<ArrayList> friendlist = new ArrayList<ArrayList>();
	//private Map<String,String> friends = new HashMap<String,String>();
  	public void setUsername(String username){
		this.username = new String(username);
	}
	public void setPassword(String password){
		this.password = new String(password);
	}
	public String getUsername(){
		return username;
	}
	public String getPassword(){
		return password;
	}
	public ArrayList<String> getFriendlist(){
		return friendlist;
	}
	public ArrayList<String> getMessage(){
		return message;
	}
	public ArrayList<String> getExperience(){
		return experience;
	}
	public ArrayList<String> getHobby(){
		return hobby;
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
			String sql1 = "select * from user";
			st = (Statement)con.createStatement();
			ResultSet res = st.executeQuery(sql1);
			boolean flag = false;
			while(res.next()){
				if(username.equals(res.getString("username")) && password.equals(res.getString("password"))){
					flag = true;
					break;
				}
			}
			if(flag){
			//	System.out.println("1111111");
				String sql2 = "select * from friend_list";
				res = st.executeQuery(sql2);
				while(res.next()){
					if(username.equals(res.getString("username")))
							friendlist.add(new String(res.getString("list_name")));
				}
			//	System.out.println("2222222");
				String sql3 = "select * from message";
				res = st.executeQuery(sql3);
				while(res.next()){
					if(username.equals(res.getString("username")))
						message.add(new String(res.getString("message_content"))+" by " + new String(res.getString("message_name")));
				}
			//	System.out.println("3333333");
				String sql4 = "select * from experience";
				res = st.executeQuery(sql4);
				while(res.next()){
					if(username.equals(res.getString("username")))
						experience.add(new String(res.getString("degree"))+" graduated from " + new String(res.getString("school")) + " now working at "+new String(res.getString("working_place")));
				}
			//	System.out.println("4444444");
				String sql5 = "select * from hobbies";
				res = st.executeQuery(sql5);
				while(res.next()){
					if(username.equals(res.getString("username")))
						hobby.add(new String(res.getString("hobby")));
				}
				con.close();
			//	System.out.println("hhhhhhhhhhhhhhhhh");
				return "Success";
			}else{
			//	System.out.println("No this User.");
				con.close();
				return "Failed";
			}
		}catch(Exception e){
		//	System.out.println("Errors."+e.getMessage());
			return "Failed";
		}
	}
}
