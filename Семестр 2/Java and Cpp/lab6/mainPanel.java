import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Collections;
import java.util.Random;
import java.util.ArrayList;

public class mainPanel extends JDialog {
    private JPanel contentPane;
    private CanvasPanel canvasPanel;
    private JButton drawButton;
    private JCheckBox coloredCheckBox;
    private JTextPane a3TextPane;

    private void createUIComponents() {
        canvasPanel = new CanvasPanel();
    }

    public Color generateColor() {
        Random rand = new Random();
        float c1 = rand.nextFloat();
        float c2 = rand.nextFloat();
        float c3 = rand.nextFloat();
        return new Color(c1, c2, c3);
    }

    class CanvasPanel extends JPanel {
        private boolean paint = false;

        public void setRadius(int r) {
            paint = true;
            repaint();
        }

        protected void paintComponent(Graphics g) {
            super.paintComponent(g);

            if (paint) {
                g.setColor(Color.BLACK);

                ArrayList<Line> linesParA = new ArrayList(), linesParB = new ArrayList(), linesParC = new ArrayList(),
                        linesParB2 = new ArrayList(), linesParD = new ArrayList(), linesParE = new ArrayList();

                // задаем точки нашего тетраэдра
                Point pointA = new Point(20, 320);
                Point pointB = new Point(175, 100);
                Point pointC = new Point(200, 380);
                Point pointD = new Point(270, 280);

                g.drawLine((int)pointB.x, (int)pointB.y, (int)pointA.x, (int)pointA.y);
                g.drawLine((int)pointA.x, (int)pointA.y, (int)pointC.x, (int)pointC.y);
                g.drawLine((int)pointB.x, (int)pointB.y, (int)pointC.x, (int)pointC.y);
                g.drawLine((int)pointB.x, (int)pointB.y, (int)pointD.x, (int)pointD.y);
                g.drawLine((int)pointC.x, (int)pointC.y, (int)pointD.x, (int)pointD.y);

                // теперь будем отрисовыать прямые

                // получаем количество отрезков
                int n = Integer.parseInt(a3TextPane.getText().toString());


                Line lineA = new Line(pointA, pointB);
                // начнем отрисовку разрезов
                ArrayList<Point> PointsonA = new ArrayList();
                for (int i = 1; i < n; ++i) {
                    double x = pointA.x + (pointB.x - pointA.x) / n * i;
                    PointsonA.add(new Point(x, lineA.find(x)));
                }

                Line lineB = new Line(pointB, pointC);
                ArrayList<Point> PointsonB = new ArrayList();
                for (int i = 1; i < n; ++i) {
                    double x = pointB.x + (pointC.x - pointB.x) / n * i;
                    PointsonB.add(new Point(x, lineB.find(x)));
                }

                Line lineC = new Line(pointA, pointC);
                ArrayList<Point> PointsonC = new ArrayList();
                for (int i = 1; i < n; ++i) {
                    double x = pointA.x + (pointC.x - pointA.x) / n * i;
                    PointsonC.add(new Point(x, lineC.find(x)));
                }

                Line lineD = new Line(pointB, pointD);
                ArrayList<Point> PointsonD = new ArrayList();
                for (int i = 1; i < n; ++i) {
                    double x = pointB.x + (pointD.x - pointB.x) / n * i;
                    PointsonD.add(new Point(x, lineD.find(x)));
                }

                Line lineE = new Line(pointC, pointD);
                ArrayList<Point> PointsonE = new ArrayList();
                for (int i = 1; i < n; ++i) {
                    double x = pointC.x + (pointD.x - pointC.x) / n * i;
                    PointsonE.add(new Point(x, lineE.find(x)));
                }

                // отрисовка линий
                linesParC.add(lineC);
                linesParA.add(lineA);


                linesParB2.add(lineB);
                linesParE.add(lineE);

                linesParD.add(lineD);

                for (int i = 1; i < n; ++i) {
                    g.drawLine((int)PointsonA.get(i-1).x, (int)PointsonA.get(i-1).y, (int)PointsonB.get(n-1-i).x, (int)PointsonB.get(n-1-i).y);
                    linesParC.add(new Line(PointsonA.get(i-1).x, PointsonA.get(i-1).y, PointsonB.get(n-1-i).x, PointsonB.get(n-1-i).y));

                    g.drawLine((int)PointsonA.get(i-1).x, (int)PointsonA.get(i-1).y, (int)PointsonC.get(i-1).x, (int)PointsonC.get(i-1).y);
                    linesParB.add(new Line(PointsonA.get(i-1).x, PointsonA.get(i-1).y, PointsonC.get(i-1).x, PointsonC.get(i-1).y));

                    g.drawLine((int)PointsonC.get(i-1).x, (int)PointsonC.get(i-1).y, (int)PointsonB.get(i-1).x, (int)PointsonB.get(i-1).y);
                    linesParA.add(new Line(PointsonC.get(i-1).x, PointsonC.get(i-1).y, PointsonB.get(i-1).x, PointsonB.get(i-1).y));

                    g.drawLine((int)PointsonB.get(i-1).x, (int)PointsonB.get(i-1).y, (int)PointsonD.get(i-1).x, (int)PointsonD.get(i-1).y);
                    linesParE.add(new Line((int)PointsonB.get(i-1).x, (int)PointsonB.get(i-1).y, (int)PointsonD.get(i-1).x, (int)PointsonD.get(i-1).y));

                    g.drawLine((int)PointsonB.get(i-1).x, (int)PointsonB.get(i-1).y, (int)PointsonE.get(n-1-i).x, (int)PointsonE.get(n-1-i).y);
                    linesParD.add(new Line((int)PointsonB.get(i-1).x, (int)PointsonB.get(i-1).y, (int)PointsonE.get(n-1-i).x, (int)PointsonE.get(n-1-i).y));

                    g.drawLine((int)PointsonD.get(i-1).x, (int)PointsonD.get(i-1).y, (int)PointsonE.get(i-1).x, (int)PointsonE.get(i-1).y);
                    linesParB2.add(new Line((int)PointsonD.get(i-1).x, (int)PointsonD.get(i-1).y, (int)PointsonE.get(i-1).x, (int)PointsonE.get(i-1).y));
                }

                linesParB.add(lineB);
                linesParE.add(lineE);

                if (coloredCheckBox.isSelected()) {
                    // заполняем левую грань
                    for (int a = 0; a < n; ++a) {
                        Point arra[] = new Point[3];
                        for (int i = 0; i < n - a; ++i) {
                            // a, a + i, i
                            g.setColor(generateColor());

                            arra[0] = linesParA.get(a).intersect(linesParB.get(a + i));
                            arra[1] = linesParA.get(a).intersect(linesParC.get(i));
                            arra[2] = linesParB.get(a + i).intersect(linesParC.get(i));
                            int xs[] = new int[]{(int) arra[0].x, (int) arra[1].x, (int) arra[2].x};
                            int ys[] = new int[]{(int) arra[0].y, (int) arra[1].y, (int) arra[2].y};
                            g.fillPolygon(xs, ys, 3);
                        }

                        for (int i = 0; i < n - a - 1; ++i) {
                            // a + 1, i + a, i + 1
                            g.setColor(generateColor());

                            arra[0] = linesParA.get(a + 1).intersect(linesParB.get(i + a));
                            arra[1] = linesParA.get(a + 1).intersect(linesParC.get(i + 1));
                            arra[2] = linesParB.get(i + a).intersect(linesParC.get(i + 1));
                            int xs[] = new int[]{(int) arra[0].x, (int) arra[1].x, (int) arra[2].x};
                            int ys[] = new int[]{(int) arra[0].y, (int) arra[1].y, (int) arra[2].y};
                            g.fillPolygon(xs, ys, 3);
                        }
                    }

                    // заполняем правую грань
                    // B2 D E
                    Collections.reverse(linesParD);
                    Collections.reverse(linesParE);

                    for (int a = 0; a < n; ++a) {
                        Point arra[] = new Point[3];
                        for (int i = 0; i < n-a; ++i) {
                            // a, a + i, i
                            g.setColor(generateColor());

                            arra[0] = linesParB2.get(a).intersect(linesParD.get((a + i)));
                            arra[1] = linesParB2.get(a).intersect(linesParE.get(i));
                            arra[2] = linesParD.get(a + i).intersect(linesParE.get(i));
                            int xs[] = new int[]{(int) arra[0].x, (int) arra[1].x, (int) arra[2].x};
                            int ys[] = new int[]{(int) arra[0].y, (int) arra[1].y, (int) arra[2].y};
                            g.fillPolygon(xs, ys, 3);
                        }


                        for (int i = 0; i < n - a - 1; ++i) {
                            // a + 1, i + a, i + 1
                            g.setColor(generateColor());

                            arra[0] = linesParB2.get(a + 1).intersect(linesParD.get(i + a));
                            arra[1] = linesParB2.get(a + 1).intersect(linesParE.get(i + 1));
                            arra[2] = linesParD.get(i + a).intersect(linesParE.get(i + 1));
                            int xs[] = new int[]{(int) arra[0].x, (int) arra[1].x, (int) arra[2].x};
                            int ys[] = new int[]{(int) arra[0].y, (int) arra[1].y, (int) arra[2].y};
                            g.fillPolygon(xs, ys, 3);
                        }
                    }

                    g.setColor(Color.BLACK);
                    for (int i = 1; i < n; ++i) {
                        g.drawLine((int)PointsonA.get(i-1).x, (int)PointsonA.get(i-1).y, (int)PointsonB.get(n-1-i).x, (int)PointsonB.get(n-1-i).y);
                        g.drawLine((int)PointsonA.get(i-1).x, (int)PointsonA.get(i-1).y, (int)PointsonC.get(i-1).x, (int)PointsonC.get(i-1).y);
                        g.drawLine((int)PointsonC.get(i-1).x, (int)PointsonC.get(i-1).y, (int)PointsonB.get(i-1).x, (int)PointsonB.get(i-1).y);
                        g.drawLine((int)PointsonB.get(i-1).x, (int)PointsonB.get(i-1).y, (int)PointsonD.get(i-1).x, (int)PointsonD.get(i-1).y);
                        g.drawLine((int)PointsonB.get(i-1).x, (int)PointsonB.get(i-1).y, (int)PointsonE.get(n-1-i).x, (int)PointsonE.get(n-1-i).y);
                        g.drawLine((int)PointsonD.get(i-1).x, (int)PointsonD.get(i-1).y, (int)PointsonE.get(i-1).x, (int)PointsonE.get(i-1).y);
                    }
                }
                paint = false;
            }
        }
    }

    public mainPanel() {
        setContentPane(contentPane);
        setModal(true);
        drawButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                canvasPanel.setRadius(2);
            }
        });
    }

    public static void main(String[] args) {
        mainPanel dialog = new mainPanel();
        dialog.setResizable(false);
        dialog.setSize(500, 500);
        dialog.pack();
        dialog.setVisible(true);
        System.exit(0);
    }
}