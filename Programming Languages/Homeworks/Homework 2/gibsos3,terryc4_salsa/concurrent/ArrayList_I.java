package concurrent;

import java.util.ArrayList;
public class ArrayList_I{
  public ArrayList<Integer> list;

  public ArrayList<Integer> getList(){
    return list;
  }

  public ArrayList_I() {
    list = new ArrayList<Integer>();
  }

  public ArrayList_I(ArrayList<Integer> l) {
    list = new ArrayList<Integer>(l);
  }

  public ArrayList_I(ArrayList_I l) {
    list = new ArrayList<Integer>(l.getList());
  }

  public ArrayList_I(Integer[] arr) {
    list = new ArrayList<Integer>();
    for (Integer i = 0; i < arr.length; i++) {
      list.add(arr[i]);
    }
  }

};