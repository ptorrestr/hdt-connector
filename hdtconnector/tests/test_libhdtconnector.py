import unittest
from hdtconnector.libhdtconnector import HDTConnector

class TestHDTConnector(unittest.TestCase):
  def test_basic_hdt(self):
    m_map = HDTConnector("etc/test.hdt")
    iter = m_map.search("", "", "")
    while iter.has_next():
      print( iter.next() )
