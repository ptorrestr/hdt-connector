import unittest
import logging

from hdt.dbpedia import DBpedia
from hdt.logger import setup_logging

setup_logging()
logger = logging.getLogger('hdt')
logger.setLevel(logging.DEBUG)

class TestDBpedia(unittest.TestCase):
  def setUp(self):
    self.c = DBpedia('/home/pablo/test.hdt')

  @unittest.skip("Full search on hdt file")
  def test_dbpedia_init(self):
    self.c.search("", "", "")
    while self.c.has_next():
      logger.info(self.c.next())

  @unittest.skip("Full search on hdt file")
  def test_dbpedia_funcs(self):
    resource = 'http://dbpedia.org/ontology/'
    res1 = self.c.get_definition(resource)
    self.assertIsNotNone(res1)
    res2 = self.c.get_is_redirect(resource, resource)
    self.assertFalse(res2)
    res3 = self.c.get_dbpedia_categories_of_res(resource)
    self.assertFalse(res3)
    res4 = self.c.get_dbpedia_classes_of_res(resource)
    self.assertIsNotNone(res4)
    res5 = self.c.get_dbpedia_labels(resource)
    res6 = self.c.disambiguation_pages(resource)
    res = self.c.get_ambigous_page(resource)
    res = self.c.select_rdfs_comment_of_resource(resource)
    res = self.c.is_disambiguation_page(resource)
    res = self.c.select_redirected_pages_to(resource)
    res = self.c.select_dbpedia_url_of_title("ontology")
    res = self.c.get_dbpedia_url_for_title("ontology")
    res = self.c.is_redirect(resource)
    logger.info(res)

