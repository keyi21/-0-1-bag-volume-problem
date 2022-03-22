import javax.swing.JFrame;
import javax.swing.JPanel;
import java.io.*;
import java.util.*;
public class main extends JPanel{
    static Scanner Cin=new Scanner(System.in);
    static int Used[];
    static int BagVolume[];

    public static void FOP() {
        int Option = ;
        System.out.println("请选择要处理的数据 (输入0-9):");
        Option=Cin.nextInt();
        if (Option>10 || Option<0) {
            System.out.println("没有该组数据");
        }
        String Data="data\\beibao"+String.valueOf(Option)+".in";
        System.out.println(Data);
        try {
            Scanner In=new Scanner(new FileReader(Data));
            m=In.nextInt();
            n=In.nextInt();
            Used=new int[10010];
            BagVolume=new int[10010];
            for (int i=1;i<=n;i++) {
                Used[i] = In.nextInt();
                BagVolume[i] = In.nextInt();
                System.out.printf("使用量: %4d 总容量: %4d \n", Used[i], BagVolume[i]);
            }
        } catch (IOException e) {
            System.out.println("没有该文件");
        }
    }

    /*
     散点图绘制
     */
    public static void PlottingScatterPlots() {
        JFrame Frame=new JFrame();
        Frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Frame.add(new main());
        Frame.setSize(233,233);
        Frame.setLocation(233,233);
        Frame.setVisible(true);
    }

    static int Res;
    static int Vectors[];


}
