import cv2
import serial
from detectron2.config import get_cfg
from detectron2 import model_zoo
from detectron2.engine import DefaultPredictor
from detectron2.utils.visualizer import Visualizer
from detectron2.data import MetadataCatalog, DatasetCatalog
import glob
import numpy as np
import time

cfg = get_cfg()
cfg.MODEL.DEVICE = 'cpu'

cfg.merge_from_file(model_zoo.get_config_file('COCO-InstanceSegmentation/mask_rcnn_R_50_FPN_3x.yaml'))
"""
import cv2
vidcap = cv2.VideoCapture('cup.mp4')
success,image = vidcap.read()
count = 0
while success:
  cv2.imwrite("frame%d.jpg" % count, image)     # save frame as JPEG file      
  success,image = vidcap.read()
  print('Read a new frame: ', success)
  count += 10
"""
cfg.MODEL.ROI_HEADS.SCORE_THRESH_TEST = 0.7

cfg.MODEL.WEIGHTS = model_zoo.get_checkpoint_url('COCO-InstanceSegmentation/mask_rcnn_R_50_FPN_3x.yaml')

res = ""

for filename in glob.iglob(r'*', recursive=True):
  if 'Cup' not in filename:
    continue
  im = cv2.imread(filename)
  model = DefaultPredictor(cfg)
  outputs = model(im)
  v = Visualizer(im[:, :, ::-1], MetadataCatalog.get(cfg.DATASETS.TRAIN[0]), scale=1.2)
  out = v.draw_instance_predictions(outputs["instances"].to("cpu"))
  instances = outputs['instances'].pred_classes.cpu().numpy()
  cup_index = []
  avg = []
  for i in range(len(instances)):
    if instances[i] == 41:
      cup_index.append(i)
  for i in cup_index:
    position = outputs['instances'].pred_boxes.tensor.cpu().numpy()[i]
    x_pos = int((position[0] + position[2]) / 2)
    y_pos = int((position[1] + position[3]) / 2)
    check = im[y_pos-10:y_pos+10, x_pos-10:x_pos+10]
    num_elem = 0
    sum = 0
    for i in check:
      for j in i:
        num_elem += 1
        sum += j[2]
    avg.append(sum / num_elem)
  cup_index = cup_index[avg.index(max(avg))]
  position = outputs['instances'].pred_boxes.tensor.cpu().numpy()[cup_index].astype(np.int32)/im.shape[1]
  x_pos = (position[0] + position[2]) / 2
  print(x_pos * 106 + 32)
  ser = serial.Serial("/dev/ttyUSB1", 115200, timeout = 1)
  ser.write(bytes((str(int(x_pos * 106 + 32)) + "\n"), "utf-8"))
  ser.close()
  cv2.imshow("x", out.get_image()[:, :, ::-1])
  cv2.waitKey(0)
  break
