import java.util.*;
import java.sql.*;

public class ShowList {
	private String username;
	private String password;
	private String list_name;
	private ArrayList<String> friendlist = new ArrayList<String>();
  	public void setUsername(String username){
		this.username = new String(username);
	}
  	public void setPassword(String password){
  		this.password = new String(password);
  	}
  	public void setList_name(String list_name){
  		this.list_name = new String(list_name);
  	}
  	public String getList_name(){
  		return list_name;
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
			String sql1 = "select * from friend";
			st = (Statement)con.createStatement();
			ResultSet res = st.executeQuery(sql1);
			list_name = list_name.replaceAll(" ","");
		//	System.out.println("mmmmmmmm  list_name="+list_name + " username="+username);
			while(res.next()){
			//	System.out.println("nnnnnnnnnnnnn");
			//	System.out.println(res.getString("username")+"  "+res.getString("list_name")+" "+res.getString("friend_name"));
				if(username.equals(res.getString("username")) && list_name.equals(res.getString("list_name"))){
					System.out.println("username="+username+" list_name="+list_name+"  "+res.getString("friend_name"));
					friendlist.add(new String(res.getString("friend_name")));
				}
			}
		//	System.out.println("sssssss");
			con.close();
			return "Success";
		}catch(Exception e){
		//	System.out.println("Errors."+e.getMessage());
			return "Failed";
		}
	}
}
