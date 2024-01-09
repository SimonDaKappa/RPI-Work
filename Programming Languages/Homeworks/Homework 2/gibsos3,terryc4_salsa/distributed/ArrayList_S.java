package distributed;

import java.util.ArrayList;
public class ArrayList_S {
  public ArrayList<String> list;

  public ArrayList_S() {
    list = new ArrayList<String>();
  }

  public ArrayList<String> getList(){
    return list;
  }

  public ArrayList_S(ArrayList<String> l) {
    list = new ArrayList<String>(l);
  }

  public ArrayList_S(String[] arr) {
    list = new ArrayList<String>();
    for (Integer i = 0; i < arr.length; i++) {
      list.add(arr[i]);
    }
  }
}
