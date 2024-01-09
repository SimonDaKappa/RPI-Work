package distributed;

public class helper {
  
  public static Integer findIndex(Object[] arr, Object x) {
    for (Integer i = 0; i < arr.length; i++) {
      if (arr[i].equals(x)) {
        return i;
      }
    }
    return -1;
  }

  public static Integer findIndex(String[] arr, String s) {
    for (Integer i = 0; i < arr.length; i++) {
      if (arr[i].equals(s)) {
        return i;
      }
    }
    return -1;
  }

  public static Integer findIndex(Integer[] arr, Integer x) {
    for (Integer i = 0; i < arr.length; i++) {
      if (arr[i].equals(x)) {
        return i;
      }
    }
    return -1;
  }
  
  public static ArrayList_S getUniqueItems(String[] c) {
    ArrayList_S arr = new ArrayList_S();
    for (Integer i = 0; i < c.length; i++) {
      if (!arr.list.contains(c[i])) {
        arr.list.add(c[i]);
      }
    }
    return arr;
  }

  public static ArrayList_I getUniqueItems(Integer[] a) {
    ArrayList_I arr = new ArrayList_I();
    for (Integer i = 0; i < a.length; i++) {
      if (!arr.list.contains(a[i])) {
        arr.list.add(a[i]);
      }
    }
    return arr;
  }

  public static ArrayList_S getUniqueItems(ArrayList_S s) {
    ArrayList_S arr = new ArrayList_S();
    for (Integer i = 0; i < s.list.size(); i++) {
      if (!arr.list.contains(s.list.get(i))) {
        arr.list.add(s.list.get(i));
      }
    }
    return arr;
  }

  public static ArrayList_I getUniqueItems(ArrayList_I a) {
    ArrayList_I arr = new ArrayList_I();
    for (Integer i = 0; i < a.list.size(); i++) {
      if (!arr.list.contains(a.list.get(i))) {
        arr.list.add(a.list.get(i));
      }
    }
    return arr;
  }

  public static Boolean arrContains(String[] arr, String s) {
    for (Integer i = 0; i < arr.length; i++) {
      if (arr[i].equals(s)) {
        return true;
      }
    }
    return false;
  }

  public static Boolean arrContains(Integer[] arr, Integer x) {
    for (Integer i = 0; i < arr.length; i++) {
      if (arr[i].equals(x)) {
        return true;
      }
    }
    return false;
  }
  
  public static String printArr(Object[] arr) {
    String ret = "";
    for (int i = 0; i < arr.length; i++) {
      ret += arr[i] + " ";
    }
    return ret;
  }

}
